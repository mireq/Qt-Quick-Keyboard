#include <QGuiApplication>
#include <QMetaObject>
#include <QQmlComponent>
#include <QQuickItem>
#include <QRectF>
#include <QUrl>
#include "../Dispatcher.h"
#include "../KeyboardItem.h"
#include "../register.h"

#include "InputContextEmbedded.h"

InputContextEmbedded::InputContextEmbedded(const QString &mainFile):
	InputContext(mainFile),
	m_component(0),
	m_keyboard(0)
{
	registerQmlTypes();
	connect(this, SIGNAL(focusObjectChanged(QObject*)), this, SLOT(onFocusObjectChanged(QObject*)));
}

InputContextEmbedded::~InputContextEmbedded()
{
}

QRectF InputContextEmbedded::keyboardRect() const
{
	if (!m_keyboard) {
		return QRectF();
	}
	return m_keyboard->property("geometry").toRectF();
}

void InputContextEmbedded::showInputPanel()
{
	if (!m_component || !m_focusWindow) {
		m_focusWindow = qobject_cast<QQuickView *>(QGuiApplication::focusWindow());
		if (m_focusWindow) {
			m_component = new QQmlComponent(m_focusWindow->engine(), QUrl(mainFile()), m_focusWindow->rootObject());
			if (m_component->isLoading()) {
				connect(m_component, SIGNAL(statusChanged(QDeclarativeComponent::Status)), this, SLOT(embedKeyboard()));
			}
			else {
				embedKeyboard();
			}
		}
	}
	InputContext::showInputPanel();
	updateVisibility();
}

void InputContextEmbedded::hideInputPanel()
{
	InputContext::hideInputPanel();
	updateVisibility();
}

void InputContextEmbedded::embedKeyboard()
{
	if (m_component->isError()) {
		qWarning() << m_component->errors();
		return;
	}

	m_keyboard = qobject_cast<QQuickItem *>(m_component->beginCreate(m_focusWindow->rootContext()));
	if (!m_keyboard) {
		qWarning() << "Root component is not QQuickItem";
		m_component->completeCreate();
		return;
	}
	QQuickItem *rootObject = m_focusWindow->rootObject();

	m_keyboard->setProperty("parent", QVariant::fromValue(qobject_cast<QQuickItem *>(m_focusWindow->rootObject())));
	m_keyboard->setParent(rootObject);
	m_keyboard->setParentItem(rootObject);

	QQuickItem *content = rootObject->findChild<QQuickItem *>("content");
	if (content) {
		m_keyboard->setProperty("content", QVariant::fromValue<QQuickItem *>(content));
	}
	updateVisibility();

	m_component->completeCreate();
	connect(m_keyboard, SIGNAL(geometryChanged()), this, SLOT(onKeyboardRectChanged()));
}

void InputContextEmbedded::onFocusObjectChanged(QObject *focusObject)
{
	if (m_keyboard) {
		QuickKeyboard::KeyboardItem *kbd = m_keyboard->findChild<QuickKeyboard::KeyboardItem *>("QuickKeyboard");
		kbd->dispatcher()->setFocusObject(focusObject);
	}
}

void InputContextEmbedded::updateVisibility()
{
	if (m_keyboard) {
		m_keyboard->setProperty("isVisible", isInputPanelVisible());
	}
}

void InputContextEmbedded::onKeyboardRectChanged()
{
	emitKeyboardRectChanged();
}
