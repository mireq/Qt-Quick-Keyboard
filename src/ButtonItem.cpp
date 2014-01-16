#include "ButtonItem.h"

ButtonItem::ButtonItem(QQuickItem *parent):
	QQuickItem(parent),
	m_pressed(false),
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

