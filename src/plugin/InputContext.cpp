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

QRectF InputContext::keyboardRect() const
{
	return QRectF();
}

void InputContext::showInputPanel()
{
	qDebug() << "show";
	m_visible = true;
	QPlatformInputContext::showInputPanel();
}

void InputContext::hideInputPanel()
{
	qDebug() << "hide";
	m_visible = false;
	QPlatformInputContext::hideInputPanel();
}

bool InputContext::isInputPanelVisible() const
{
	return m_visible;
}

void InputContext::setFocusObject(QObject *object)
{
}

