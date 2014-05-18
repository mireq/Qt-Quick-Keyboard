#include "KeyboardItem.h"

KeyboardItem::KeyboardItem(QQuickItem *parent):
	QQuickItem(parent),
	m_mode(0)
{
}

KeyboardItem::~KeyboardItem()
{
}

void KeyboardItem::setMode(ModeItem *mode)
{
	if (m_mode == mode) {
		return;
	}

	if (m_mode) {
		m_mode->setVisible(false);
		disconnect(m_mode, SIGNAL(symbolTriggered(const QString &)), this, SLOT(onSymbolTriggered(const QString &)));
	}

	m_mode = mode;
	if (mode) {
		mode->setVisible(true);
		connect(mode, SIGNAL(symbolTriggered(const QString &)), this, SLOT(onSymbolTriggered(const QString &)));
	}
	emit modeChanged(m_mode);
}

void KeyboardItem::onSymbolTriggered(const QString &symbol)
{
}

