#include "InputContext.h"


InputContext::InputContext():
	m_visible(false)
{
}

InputContext::~InputContext()
{
}

bool InputContext::isValid() const
{
	return true;
}

void InputContext::showInputPanel()
{
	m_visible = true;
	QPlatformInputContext::showInputPanel();
	emitInputPanelVisibleChanged();
}

void InputContext::hideInputPanel()
{
	m_visible = false;
	QPlatformInputContext::hideInputPanel();
	emitInputPanelVisibleChanged();
}

bool InputContext::isInputPanelVisible() const
{
	return m_focusObject && m_visible;
}

void InputContext::setFocusObject(QObject *object)
{
	m_focusObject = object;
	if (m_visible) {
		if (m_focusObject) {
			showInputPanel();
		}
		else {
			hideInputPanel();
		}
	}
	emit focusObjectChanged(m_focusObject);
}

