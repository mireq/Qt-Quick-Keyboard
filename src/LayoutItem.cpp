#include <QtGlobal>
#include "ButtonItem.h"
#include "LayoutItem.h"

#include <QDebug>

LayoutItemAttached::LayoutItemAttached(QObject *parent):
	QObject(parent),
	m_col(0),
	m_row(0),
	m_colSpan(1),
	m_rowSpan(1)
{
}

LayoutItemAttached::~LayoutItemAttached()
{
}

LayoutItem::LayoutItem(QQuickItem *parent):
	BaseLayoutItem(parent),
	m_rows(0),
	m_cols(0),
	m_autoSize(true)
{
	setFlag(QQuickItem::ItemHasContents);
	setKeepTouchGrab(true);
	setAcceptedMouseButtons(Qt::LeftButton);
	m_touchPositions << QPointF();
}

LayoutItem::~LayoutItem()
{
}

void LayoutItem::addButton(ButtonItem *button)
{
	BaseLayoutItem::addButton(button);
	if (m_autoSize) {
		setRowsSimple(qMax(m_rows, layoutProperty(button, "row", 0) + layoutProperty(button, "rowSpan", 1)));
		setColsSimple(qMax(m_cols, layoutProperty(button, "col", 0) + layoutProperty(button, "colSpan", 1)));
	}

	QObject *layoutAttached = qmlAttachedPropertiesObject<LayoutItem>(button);
	if (layoutAttached) {
		connect(layoutAttached, SIGNAL(colChanged(int)), SLOT(recalculateRowColSize()));
		connect(layoutAttached, SIGNAL(rowChanged(int)), SLOT(recalculateRowColSize()));
		connect(layoutAttached, SIGNAL(colSpanChanged(int)), SLOT(recalculateRowColSize()));
		connect(layoutAttached, SIGNAL(rowSpanChanged(int)), SLOT(recalculateRowColSize()));
	}
}

void LayoutItem::clearButtons()
{
	foreach (const ButtonItem *button, buttons()) {
		QObject *layoutAttached = qmlAttachedPropertiesObject<LayoutItem>(button);
		if (layoutAttached) {
			disconnect(layoutAttached, SIGNAL(colChanged(int)), this, SLOT(recalculateRowColSize()));
			disconnect(layoutAttached, SIGNAL(rowChanged(int)), this, SLOT(recalculateRowColSize()));
			disconnect(layoutAttached, SIGNAL(colSpanChanged(int)), this, SLOT(recalculateRowColSize()));
			disconnect(layoutAttached, SIGNAL(rowSpanChanged(int)), this, SLOT(recalculateRowColSize()));
		}
	}
	if (m_autoSize) {
		setRowsSimple(0);
		setColsSimple(0);
	}
	BaseLayoutItem::clearButtons();
}

void LayoutItem::setCols(int cols)
{
	m_autoSize = false;
	setColsSimple(cols);
}

void LayoutItem::setRows(int rows)
{
	m_autoSize = false;
	setRowsSimple(rows);
}

LayoutItemAttached *LayoutItem::qmlAttachedProperties(QObject *object)
{
	return new LayoutItemAttached(object);
}

void LayoutItem::setColsSimple(int cols)
{
	if (m_cols == cols) {
		return;
	}

	m_cols = cols;
	recalculatePositions();
}

void LayoutItem::synchronizeActivePoints()
{
	foreach (ButtonItem *button, buttons()) {
		bool buttonActive = button->isActive();
		bool pointActive = checkActive(button);
		if (buttonActive && !pointActive) {
			button->setActive(false);
		}
		if (!buttonActive && pointActive) {
			button->setActive(true);
		}
	}
}

void LayoutItem::setRowsSimple(int rows)
{
	if (m_rows == rows) {
		return;
	}

	m_rows = rows;
	recalculatePositions();
}

void LayoutItem::triggerOnPosition(int x, int y)
{
	QPointF point(x, y);
	foreach (ButtonItem *button, buttons()) {
		if (button->contains(button->mapFromScene(point))) {
			emit button->triggered();
		}
	}
}

void LayoutItem::setMousePosition(const QPointF &position)
{
	m_touchPositions[0] = position;
	synchronizeActivePoints();
}

void LayoutItem::setTouchPositions(const QList<QPointF> &positions)
{
	m_touchPositions = QList<QPointF>() << m_touchPositions[0];
	m_touchPositions += positions;
	synchronizeActivePoints();
}

bool LayoutItem::checkActive(const ButtonItem *button) const
{
	foreach (const QPointF &point, m_touchPositions) {
		if (!point.isNull()) {
			if (button->contains(button->mapFromScene(point))) {
				return true;
			}
		}
	}
	return false;
}

void LayoutItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
	BaseLayoutItem::geometryChanged(newGeometry, oldGeometry);
	recalculatePositions();
}

void LayoutItem::touchEvent(QTouchEvent *event)
{
	QVector<QPointF> points;
	points.reserve(event->touchPoints().length());
	foreach (const QTouchEvent::TouchPoint &point, event->touchPoints()) {
		points << point.scenePos();
	}
	setTouchPositions(points.toList());

	QVector<QPointF> pointsAfterRelease;
	pointsAfterRelease.reserve(event->touchPoints().length());
	foreach (const QTouchEvent::TouchPoint &point, event->touchPoints()) {
		if (point.state() == Qt::TouchPointReleased) {
			pointsAfterRelease << QPointF();
			triggerOnPosition(point.rect().x(), point.rect().y());
		}
		else {
			pointsAfterRelease << point.pos().toPoint();
		}
	}

	if (points != pointsAfterRelease) {
		setTouchPositions(pointsAfterRelease.toList());
	}
}

void LayoutItem::mouseMoveEvent(QMouseEvent *event)
{
	event->accept();
	setMousePosition(QPointF(event->x(), event->y()));
}

void LayoutItem::mousePressEvent(QMouseEvent *event)
{
	event->accept();
	setMousePosition(QPointF(event->x(), event->y()));
}

void LayoutItem::mouseReleaseEvent(QMouseEvent *event)
{
	event->accept();
	triggerOnPosition(event->x(), event->y());
	setMousePosition(QPointF());
}

int LayoutItem::layoutProperty(const ButtonItem *button, const char *property, int fallback)
{
	QObject *layoutAttached = qmlAttachedPropertiesObject<LayoutItem>(button);
	if (!layoutAttached) {
		return fallback;
	}
	return layoutAttached->property(property).toInt();
}

void LayoutItem::recalculateRowColSize()
{
	if (!m_autoSize) {
		return;
	}
	int rows = 0;
	int cols = 0;
	foreach (const ButtonItem *button, buttons()) {
		rows = qMax(layoutProperty(button, "row", 0) + layoutProperty(button, "rowSpan", 1), rows);
		cols = qMax(layoutProperty(button, "col", 0) + layoutProperty(button, "colSpan", 1), cols);
	}
	setRowsSimple(rows);
	setColsSimple(cols);
}

void LayoutItem::recalculatePositions()
{
	if (m_rows == 0 || m_cols == 0) {
		return;
	}

	int w = width();
	int h = height();

	foreach (ButtonItem *button, buttons()) {
		QObject *layoutAttached = qmlAttachedPropertiesObject<LayoutItem>(button);
		if (!layoutAttached) {
			continue;
		}

		int left = layoutAttached->property("col").toInt();
		int top = layoutAttached->property("row").toInt();
		int right = layoutAttached->property("colSpan").toInt() + left;
		int bottom = layoutAttached->property("rowSpan").toInt() + top;

		int x = left * w / m_cols;
		int y = top * h / m_rows;

		button->setProperty("x", x);
		button->setProperty("y", y);
		button->setProperty("width", right * w / m_cols - x);
		button->setProperty("height", bottom * h / m_rows - y);
	}
}

