#include <QGuiApplication>
#include <QInputMethodEvent>
#include <QKeyEvent>
#include <QWindow>
#include "Dispatcher.h"


Dispatcher::Dispatcher(QObject *parent):
	QObject(parent),
	m_focusObject(0)
{
}

Dispatcher::~Dispatcher()
{
}

QObject *Dispatcher::focusObject() const
{
	return m_focusObject;
}

void Dispatcher::setFocusObject(QObject *focusObject)
{
	m_focusObject = focusObject;
}

void Dispatcher::sendSymbol(const QString &symbol)
{
	if (!m_focusObject) {
		return;
	}

	QInputMethodEvent ev;
	if (symbol == QString("\x7f")) { // backspace
		ev.setCommitString("", -1, 1);
	}
	else if (symbol == QString("\n")) {
		QWindow *mainView = QGuiApplication::focusWindow();
		QKeyEvent *press = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
		QGuiApplication::postEvent(mainView, press);
		QKeyEvent *release = new QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Return, Qt::NoModifier);
		QGuiApplication::postEvent(mainView, release);
		return;
	}
	else {
		ev.setCommitString(symbol);
	}
	QCoreApplication::sendEvent(m_focusObject, &ev);
}


