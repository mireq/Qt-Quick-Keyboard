#ifndef BASELAYOUTITEM_H_ZHXO0UI7
#define BASELAYOUTITEM_H_ZHXO0UI7

#include <QQuickItem>
#include <QList>
class ButtonItem;

class BaseLayoutItem: public QQuickItem
{
Q_OBJECT
public:
	explicit BaseLayoutItem(QQuickItem *parent = 0);
	~BaseLayoutItem();

	virtual void addButton(ButtonItem *button);
	virtual void clearButtons();

protected:
	const QList<ButtonItem *> &buttons() const;

private:
	QList<ButtonItem *> m_buttons;
}; /* -----  end of class BaseLayoutItem  ----- */

#endif /* end of include guard: BASELAYOUTITEM_H_ZHXO0UI7 */

