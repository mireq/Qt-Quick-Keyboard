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
	}

	m_mode = mode;
	mode->setVisible(true);
	emit modeChanged(m_mode);
}

