#include "ButtonItem.h"

ButtonItem::ButtonItem(QQuickItem *parent):
	QQuickItem(parent),
	m_active(false),
	m_modifier(false),
	m_col(0),
	m_row(0),
	m_colSpan(1),
	m_rowSpan(1)
{
}

ButtonItem::~ButtonItem()
{
}

void ButtonItem::setActive(bool active)
{
	if (m_active == active) {
		return;
	}

	m_active = active;
	emit activeChanged(active);
}

