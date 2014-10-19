#ifndef GRIDLAYOUTITEM_H_KEQWS1DN
#define GRIDLAYOUTITEM_H_KEQWS1DN


#include <QList>
#include "LayoutItem.h"

namespace QuickKeyboard
{

class GridLayoutItem;

class GridLayoutItemAttached: public QObject
{
Q_OBJECT
Q_PROPERTY(int col MEMBER m_col NOTIFY colChanged)
Q_PROPERTY(int row MEMBER m_row NOTIFY rowChanged)
Q_PROPERTY(int colSpan MEMBER m_colSpan NOTIFY colSpanChanged)
Q_PROPERTY(int rowSpan MEMBER m_rowSpan NOTIFY rowSpanChanged)
Q_PROPERTY(QuickKeyboard::GridLayoutItem *layout READ layout)
public:
	explicit GridLayoutItemAttached(QObject *parent = 0);
	~GridLayoutItemAttached();
	GridLayoutItem *layout() const;

signals:
	void colChanged(int col);
	void rowChanged(int row);
	void colSpanChanged(int colSpan);
	void rowSpanChanged(int rowSpan);

private:
	int m_col;
	int m_row;
	int m_colSpan;
	int m_rowSpan;
}; /* -----  end of class GridLayoutItemAttached  ----- */


class GridLayoutItem: public LayoutItem
{
Q_OBJECT
Q_PROPERTY(int cols MEMBER m_cols WRITE setCols NOTIFY colsChanged)
Q_PROPERTY(int rows MEMBER m_rows WRITE setRows NOTIFY rowsChanged)
public:
	explicit GridLayoutItem(QQuickItem *parent = 0);
	~GridLayoutItem();

	void addButton(ButtonItem *button);
	void clearButtons();

	void setCols(int cols);
	void setRows(int rows);

	static GridLayoutItemAttached *qmlAttachedProperties(QObject *object);

public slots:
	void redirectEventsToItem(QQuickItem *item);

private:
	void setColsSimple(int cols);
	void setRowsSimple(int rows);

private:
	void triggerOnPosition(const QPointF &point);

	void setMousePosition(const QPointF &position);
	void setTouchPositions(const QList<QPointF> &positions);

	bool checkMouseDown(const ButtonItem *button) const;

	static bool checkButtonAtPoint(const ButtonItem *button, const QPointF &point);

signals:
	void colsChanged(int cols);
	void rowsChanged(int rows);

protected:
	virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
	virtual void touchEvent(QTouchEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

private:
	static int layoutProperty(const ButtonItem *button, const char *property, int fallback);

private slots:
	void recalculateRowColSize();
	void recalculatePositions();
	void synchronizeMouseDownPoints();

private:
	int m_rows;
	int m_cols;
	bool m_autoSize;

	QList<QPointF> m_touchPositions;
	QList<QTouchEvent::TouchPoint> m_touchPoints;
}; /* -----  end of class GridLayoutItem  ----- */

} /* QuickKeyboard */

QML_DECLARE_TYPEINFO(QuickKeyboard::GridLayoutItem, QML_HAS_ATTACHED_PROPERTIES)

#endif /* end of include guard: GRIDLAYOUTITEM_H_KEQWS1DN */

