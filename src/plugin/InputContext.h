#ifndef INPUTCONTEXT_CPP_Q5U7KLYO
#define INPUTCONTEXT_CPP_Q5U7KLYO

#include <qpa/qplatforminputcontext.h>
#include <QPointer>

class InputContext: public QPlatformInputContext
{
Q_OBJECT
public:
	InputContext();
	~InputContext();

	bool isValid() const;

	void showInputPanel();
	void hideInputPanel();
	bool isInputPanelVisible() const;
	void setFocusObject(QObject *object);

signals:
	void focusObjectChanged(QObject *object);

private:
	bool m_visible;
	QPointer<QObject> m_focusObject;
}; /* -----  end of class InputContext  ----- */

#endif /* end of include guard: INPUTCONTEXT_CPP_Q5U7KLYO */
