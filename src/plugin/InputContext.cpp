#include "InputContext.h"
#include <QRectF>

#include <QDebug>

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
}

void InputContext::hideInputPanel()
{
	m_visible = false;
	QPlatformInputContext::hideInputPanel();
}

bool InputContext::isInputPanelVisible() const
{
	return m_visible;
}

void InputContext::setFocusObject(QObject *object)
{
	m_focusObject = object;
}

