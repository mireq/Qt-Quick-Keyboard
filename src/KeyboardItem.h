#ifndef KEYBOARDITEM_H_PT4SCIAV
#define KEYBOARDITEM_H_PT4SCIAV

#include <QQuickItem>
#include <QList>

class ModeItem;
class Dispatcher;

class KeyboardItem: public QQuickItem
{
Q_OBJECT
Q_PROPERTY(ModeItem* mode MEMBER m_mode WRITE setMode NOTIFY modeChanged DESIGNABLE false)
Q_PROPERTY(Dispatcher* dispatcher MEMBER m_dispatcher)
public:
	explicit KeyboardItem(QQuickItem *parent = 0);
	~KeyboardItem();

	void setMode(ModeItem *mode);

signals:
	void modeChanged(ModeItem *mode);

private slots:
	void onSymbolTriggered(const QString &symbol);

private:
	ModeItem *m_mode;
	Dispatcher *m_dispatcher;
}; /* -----  end of class KeyboardItem  ----- */

#endif /* end of include guard: KEYBOARDITEM_H_PT4SCIAV */

