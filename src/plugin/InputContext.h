#ifndef INPUTCONTEXT_CPP_Q5U7KLYO
#define INPUTCONTEXT_CPP_Q5U7KLYO

#include <qpa/qplatforminputcontext.h>

class InputContext: public QPlatformInputContext
{
Q_OBJECT
public:
	InputContext();
	~InputContext();

	bool isValid() const;
	QRectF keyboardRect() const;

	void showInputPanel();
	void hideInputPanel();
	bool isInputPanelVisible() const;
	void setFocusObject(QObject *object);

private:
	bool m_visible;
}; /* -----  end of class InputContext  ----- */

#endif /* end of include guard: INPUTCONTEXT_CPP_Q5U7KLYO */
