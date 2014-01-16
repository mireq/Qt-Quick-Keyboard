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

	m_mode = mode;
	emit modeChanged(m_mode);
}

