#include <QtGlobal>
#include "ButtonItem.h"
#include "LayoutItem.h"

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
	m_cols(0)
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
	setRows(qMax(m_rows, layoutProperty(button, "row", 0) + layoutProperty(button, "rowSpan", 1)));
	setCols(qMax(m_cols, layoutProperty(button, "col", 0) + layoutProperty(button, "colSpan", 1)));

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
	BaseLayoutItem::clearButtons();
	setRows(0);
	setCols(0);
}

LayoutItemAttached *LayoutItem::qmlAttachedProperties(QObject *object)
{
	return new LayoutItemAttached(object);
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

void LayoutItem::setCols(int cols)
{
	if (m_cols == cols) {
		return;
	}

	m_cols = cols;
	recalculatePositions();
}

void LayoutItem::setRows(int rows)
{
	if (m_rows == rows) {
		return;
	}

	m_rows = rows;
	recalculatePositions();
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
	int rows = 0;
	int cols = 0;
	foreach (const ButtonItem *button, buttons()) {
		rows = qMax(layoutProperty(button, "row", 0) + layoutProperty(button, "rowSpan", 1), rows);
		cols = qMax(layoutProperty(button, "col", 0) + layoutProperty(button, "colSpan", 1), cols);
	}
	setRows(rows);
	setCols(cols);
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

