#include "ButtonItem.h"
#include "BaseLayoutItem.h"

BaseLayoutItem::BaseLayoutItem(QQuickItem *parent):
	QQuickItem(parent)
{
}

BaseLayoutItem::~BaseLayoutItem()
{
}

void BaseLayoutItem::addButton(ButtonItem *button)
{
	m_buttons.append(button);
}

void BaseLayoutItem::clearButtons()
{
	m_buttons.clear();
}

const QList<ButtonItem *> &BaseLayoutItem::buttons() const
{
	return m_buttons;
}

