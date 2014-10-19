#include <QtGlobal>
#include <QQuickWindow>
#include "ButtonItem.h"
#include "ModeItem.h"
#include "GridLayoutItem.h"

namespace QuickKeyboard
{

GridLayoutItemAttached::GridLayoutItemAttached(QObject *parent):
	QObject(parent),
	m_col(0),
	m_row(0),
	m_colSpan(1),
	m_rowSpan(1)
{
}

GridLayoutItemAttached::~GridLayoutItemAttached()
{
}

GridLayoutItem *GridLayoutItemAttached::layout() const
{
	QObject *predecessor = parent();
	ModeItem *mode = 0;
	while (predecessor != 0) {
		predecessor = predecessor->parent();
		mode = qobject_cast<ModeItem *>(predecessor);
		if (mode) {
			return qobject_cast<GridLayoutItem *>(mode->layout());
		}
	}
	return 0;
}

GridLayoutItem::GridLayoutItem(QQuickItem *parent):
	LayoutItem(parent),
	m_rows(0),
	m_cols(0),
	m_autoSize(true)
{
	setFlag(QQuickItem::ItemHasContents);
	setAcceptedMouseButtons(Qt::LeftButton);
	setZ(1);
	m_touchPositions << QPointF();
}

GridLayoutItem::~GridLayoutItem()
{
}

void GridLayoutItem::addButton(ButtonItem *button)
{
	LayoutItem::addButton(button);
	if (m_autoSize) {
		setRowsSimple(qMax(m_rows, layoutProperty(button, "row", 0) + layoutProperty(button, "rowSpan", 1)));
		setColsSimple(qMax(m_cols, layoutProperty(button, "col", 0) + layoutProperty(button, "colSpan", 1)));
	}
	connect(button, SIGNAL(triggered()), this, SLOT(synchronizeMouseDownPoints()));

	QObject *layoutAttached = qmlAttachedPropertiesObject<GridLayoutItem>(button);
	if (layoutAttached) {
		connect(layoutAttached, SIGNAL(colChanged(int)), SLOT(recalculateRowColSize()));
		connect(layoutAttached, SIGNAL(rowChanged(int)), SLOT(recalculateRowColSize()));
		connect(layoutAttached, SIGNAL(colSpanChanged(int)), SLOT(recalculateRowColSize()));
		connect(layoutAttached, SIGNAL(rowSpanChanged(int)), SLOT(recalculateRowColSize()));
	}
}

void GridLayoutItem::clearButtons()
{
	foreach (const ButtonItem *button, buttons()) {
		QObject *layoutAttached = qmlAttachedPropertiesObject<GridLayoutItem>(button);
		if (layoutAttached) {
			disconnect(layoutAttached, SIGNAL(colChanged(int)), this, SLOT(recalculateRowColSize()));
			disconnect(layoutAttached, SIGNAL(rowChanged(int)), this, SLOT(recalculateRowColSize()));
			disconnect(layoutAttached, SIGNAL(colSpanChanged(int)), this, SLOT(recalculateRowColSize()));
			disconnect(layoutAttached, SIGNAL(rowSpanChanged(int)), this, SLOT(recalculateRowColSize()));
			disconnect(button, SIGNAL(triggered()), this, SLOT(synchronizeMouseDownPoints()));
		}
	}
	if (m_autoSize) {
		setRowsSimple(0);
		setColsSimple(0);
	}
	LayoutItem::clearButtons();
}

void GridLayoutItem::setCols(int cols)
{
	m_autoSize = false;
	setColsSimple(cols);
}

void GridLayoutItem::setRows(int rows)
{
	m_autoSize = false;
	setRowsSimple(rows);
}

GridLayoutItemAttached *GridLayoutItem::qmlAttachedProperties(QObject *object)
{
	return new GridLayoutItemAttached(object);
}

void GridLayoutItem::redirectEventsToItem(QQuickItem *item)
{
	if (!item) {
		return;
	}

	if (!m_touchPositions[0].isNull()) {
		ungrabMouse();
		QMouseEvent pressEvent(QMouseEvent::MouseButtonPress, QPointF(0, 0), Qt::LeftButton, Qt::LeftButton, 0);
		window()->sendEvent(item, &pressEvent);
		item->grabMouse();
	}
	if (!m_touchPoints.isEmpty()) {
		ungrabTouchPoints();

		QVector<int> ids;
		foreach (const QTouchEvent::TouchPoint &point, m_touchPoints) {
			ids << point.id();
		}

		QTouchEvent touchEvent(
			QEvent::TouchBegin,
			(QTouchDevice *)QTouchDevice::devices().first(),
			Qt::NoModifier,
			Qt::TouchPointPressed,
			m_touchPoints
		);

		window()->sendEvent(item, &touchEvent);
		item->grabTouchPoints(ids);
	}

	m_touchPositions.clear();
	m_touchPositions << QPointF();
	m_touchPoints.clear();
}

void GridLayoutItem::setColsSimple(int cols)
{
	if (m_cols == cols) {
		return;
	}

	m_cols = cols;
	recalculatePositions();
}

void GridLayoutItem::setRowsSimple(int rows)
{
	if (m_rows == rows) {
		return;
	}

	m_rows = rows;
	recalculatePositions();
}

void GridLayoutItem::triggerOnPosition(const QPointF &point)
{
	foreach (ButtonItem *button, buttons()) {
		if (checkButtonAtPoint(button, point)) {
			emit button->released();
		}
	}
}

void GridLayoutItem::setMousePosition(const QPointF &position)
{
	m_touchPositions[0] = position;
	synchronizeMouseDownPoints();
}

void GridLayoutItem::setTouchPositions(const QList<QPointF> &positions)
{
	m_touchPositions = QList<QPointF>() << m_touchPositions[0];
	m_touchPositions += positions;
	synchronizeMouseDownPoints();
}

bool GridLayoutItem::checkMouseDown(const ButtonItem *button) const
{
	foreach (const QPointF &point, m_touchPositions) {
		if (!point.isNull()) {
			if (checkButtonAtPoint(button, point)) {
				return true;
			}
		}
	}
	return false;
}

inline bool GridLayoutItem::checkButtonAtPoint(const ButtonItem *button, const QPointF &point)
{
	QPointF mapped = point - QPointF(button->x(), button->y());
	if (mapped.x() >= 0.0f && mapped.y() >= 0.0f && mapped.x() < button->width() && mapped.y() < button->height()) {
		return true;
	}
	return false;
}

void GridLayoutItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
	LayoutItem::geometryChanged(newGeometry, oldGeometry);
	recalculatePositions();
}

void GridLayoutItem::touchEvent(QTouchEvent *event)
{
	QVector<QPointF> points;
	m_touchPoints = event->touchPoints();
	points.reserve(m_touchPoints.length());
	foreach (const QTouchEvent::TouchPoint &point, m_touchPoints) {
		points << point.pos();
	}
	setTouchPositions(points.toList());

	QVector<QPointF> pointsAfterRelease;
	pointsAfterRelease.reserve(m_touchPoints.length());
	foreach (const QTouchEvent::TouchPoint &point, m_touchPoints) {
		if (point.state() == Qt::TouchPointReleased) {
			pointsAfterRelease << QPointF();
			triggerOnPosition(point.pos());
		}
		else {
			pointsAfterRelease << point.pos().toPoint();
		}
	}

	if (points != pointsAfterRelease) {
		setTouchPositions(pointsAfterRelease.toList());
	}
}

void GridLayoutItem::mouseMoveEvent(QMouseEvent *event)
{
	QPointF scenePos = QPointF(event->x(), event->y());
	setMousePosition(scenePos);
}

void GridLayoutItem::mousePressEvent(QMouseEvent *event)
{
	QPointF scenePos = QPointF(event->x(), event->y());
	setMousePosition(scenePos);
}

void GridLayoutItem::mouseReleaseEvent(QMouseEvent *event)
{
	QPointF scenePos = QPointF(event->x(), event->y());
	triggerOnPosition(scenePos);
	setMousePosition(QPointF());
}

int GridLayoutItem::layoutProperty(const ButtonItem *button, const char *property, int fallback)
{
	QObject *layoutAttached = qmlAttachedPropertiesObject<GridLayoutItem>(button);
	if (!layoutAttached) {
		return fallback;
	}
	return layoutAttached->property(property).toInt();
}

void GridLayoutItem::recalculateRowColSize()
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

void GridLayoutItem::recalculatePositions()
{
	if (m_rows == 0 || m_cols == 0) {
		return;
	}

	int w = width();
	int h = height();

	foreach (ButtonItem *button, buttons()) {
		QObject *layoutAttached = qmlAttachedPropertiesObject<GridLayoutItem>(button);
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

void GridLayoutItem::synchronizeMouseDownPoints()
{
	foreach (ButtonItem *button, buttons()) {
		bool buttonMouseDown = button->isMouseDown();
		bool pointMouseDown = checkMouseDown(button);
		if (buttonMouseDown && !pointMouseDown) {
			button->setMouseDown(false);
		}
		if (!buttonMouseDown && pointMouseDown) {
			button->setMouseDown(true);
		}
	}
}

} /* QuickKeyboard */

