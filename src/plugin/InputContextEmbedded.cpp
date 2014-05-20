#include <QGuiApplication>
#include <QQmlComponent>
#include <QQuickItem>
#include <QRectF>
#include <QUrl>

#include "InputContextEmbedded.h"

InputContextEmbedded::InputContextEmbedded():
	InputContext(),
	m_component(0)
{
}

InputContextEmbedded::~InputContextEmbedded()
{
}

QRectF InputContextEmbedded::keyboardRect() const
{
	return QRectF();
}

void InputContextEmbedded::showInputPanel()
{
	if (!m_component || !m_focusWindow) {
		m_focusWindow = qobject_cast<QQuickView *>(QGuiApplication::focusWindow());
		if (m_focusWindow) {
			m_component = new QQmlComponent(m_focusWindow->engine(), QUrl("qrc:/quickkeyboard/keyboard.qml"), m_focusWindow->rootObject());
			if (m_component->isLoading()) {
				connect(m_component, SIGNAL(statusChanged(QDeclarativeComponent::Status)), this, SLOT(embedKeyboard()));
			}
			else {
				embedKeyboard();
			}
		}
	}
	InputContext::showInputPanel();
}

void InputContextEmbedded::hideInputPanel()
{
	InputContext::hideInputPanel();
}

void InputContextEmbedded::embedKeyboard()
{
	if (m_component->isError()) {
		qWarning() << m_component->errors();
		return;
	}

	QQuickItem *keyboard = qobject_cast<QQuickItem *>(m_component->create(m_focusWindow->rootContext()));
	if (!keyboard) {
		qWarning() << "Root component is not QQuickItem";
		return;
	}
	QQuickItem *rootObject = m_focusWindow->rootObject();

	keyboard->setParent(rootObject);
	keyboard->setParentItem(rootObject);
}

