#ifndef LAYOUTITEM_H_KEQWS1DN
#define LAYOUTITEM_H_KEQWS1DN


#include <QList>
#include "BaseLayoutItem.h"


class LayoutItemAttached: public QObject
{
Q_OBJECT
Q_PROPERTY(int col MEMBER m_col NOTIFY colChanged)
Q_PROPERTY(int row MEMBER m_row NOTIFY rowChanged)
Q_PROPERTY(int colSpan MEMBER m_colSpan NOTIFY colSpanChanged)
Q_PROPERTY(int rowSpan MEMBER m_rowSpan NOTIFY rowSpanChanged)
public:
	explicit LayoutItemAttached(QObject *parent = 0);
	~LayoutItemAttached();

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
}; /* -----  end of class LayoutItemAttached  ----- */


class LayoutItem: public BaseLayoutItem
{
Q_OBJECT
Q_PROPERTY(int cols MEMBER m_cols WRITE setCols NOTIFY colsChanged)
Q_PROPERTY(int rows MEMBER m_rows WRITE setRows NOTIFY rowsChanged)
public:
	explicit LayoutItem(QQuickItem *parent = 0);
	~LayoutItem();

	void addButton(ButtonItem *button);
	void clearButtons();

	void setCols(int cols);
	void setRows(int rows);

	static LayoutItemAttached *qmlAttachedProperties(QObject *object);

private:
	void setColsSimple(int cols);
	void setRowsSimple(int rows);

	void synchronizeActivePoints();

	void triggerOnPosition(int x, int y);

	void setMousePosition(const QPointF &position);
	void setTouchPositions(const QList<QPointF> &positions);

	bool checkActive(const ButtonItem *button) const;

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

private:
	int m_rows;
	int m_cols;
	bool m_autoSize;

	QList<QPointF> m_touchPositions;
}; /* -----  end of class LayoutItem  ----- */

QML_DECLARE_TYPEINFO(LayoutItem, QML_HAS_ATTACHED_PROPERTIES)

#endif /* end of include guard: LAYOUTITEM_H_KEQWS1DN */

