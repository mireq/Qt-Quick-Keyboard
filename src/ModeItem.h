#ifndef MODEITEM_H_6ZH81LSX
#define MODEITEM_H_6ZH81LSX

#include <QQuickItem>
#include <QList>
class ButtonItem;
class BaseLayoutItem;

class ModeItem: public QQuickItem
{
Q_OBJECT
Q_PROPERTY(BaseLayoutItem* layout READ layout WRITE setLayout NOTIFY layoutChanged)
Q_PROPERTY(QQmlListProperty<ButtonItem> buttons READ buttons DESIGNABLE false)
Q_CLASSINFO("DefaultProperty", "buttons")
public:
	explicit ModeItem(QQuickItem *parent = 0);
	~ModeItem();

	// layout property
	BaseLayoutItem *layout() const;
	void setLayout(BaseLayoutItem *layout);

	// buttons property
	QQmlListProperty<ButtonItem> buttons();
	static void buttons_append(QQmlListProperty<ButtonItem> *property, ButtonItem *mode);
	static int buttons_count(QQmlListProperty<ButtonItem> *property);
	static ButtonItem *buttons_at(QQmlListProperty<ButtonItem> *property, int idx);
	static void buttons_clear(QQmlListProperty<ButtonItem> *property);

signals:
	void layoutChanged(BaseLayoutItem *layout);
	void colsChanged(int cols);
	void rowsChanged(int rows);

private:
	BaseLayoutItem *m_layout;
	QList<ButtonItem *> m_buttons;
	int m_cols;
	int m_rows;
}; /* -----  end of class ModeItem  ----- */

#endif /* end of include guard: MODEITEM_H_6ZH81LSX */

