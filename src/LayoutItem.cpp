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
	setAcceptedMouseButtons(Qt::LeftButton);
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

void LayoutItem::setRowsSimple(int rows)
{
	if (m_rows == rows) {
		return;
	}

	m_rows = rows;
	recalculatePositions();
}

void LayoutItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
	BaseLayoutItem::geometryChanged(newGeometry, oldGeometry);
	recalculatePositions();
}

void LayoutItem::mouseMoveEvent(QMouseEvent *event)
{
	QQuickItem::mouseMoveEvent(event);
}

void LayoutItem::mousePressEvent(QMouseEvent *event)
{
	event->accept();
}

void LayoutItem::mouseReleaseEvent(QMouseEvent *event)
{
	event->accept();
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

