#include <QChildEvent>
#include "ButtonItem.h"
#include "LayoutItem.h"
#include "ModeItem.h"

ModeItem::ModeItem(QQuickItem *parent):
	QQuickItem(parent),
	m_layout(0)
{
	setVisible(false);
	setLayout(new LayoutItem());
}

ModeItem::~ModeItem()
{
}

LayoutItem *ModeItem::layout() const
{
	return m_layout;
}

void ModeItem::setLayout(LayoutItem *layout)
{
	if (m_layout == layout) {
		return;
	}

	if (m_layout) {
		m_layout->setParentItem(0);
		delete m_layout;
	}

	if (layout) {
		layout->setParentItem(this);
		foreach (ButtonItem *button, m_buttons) {
			m_layout->addButton(button);
		}
		layout->property("anchors").value<QObject *>()->setProperty("fill", QVariant::fromValue<QQuickItem *>(this));
	}
	m_layout = layout;
}

QQmlListProperty<ButtonItem> ModeItem::buttons()
{
	return QQmlListProperty<ButtonItem>(
		this,
		&m_buttons,
		&ModeItem::buttons_append,
		&ModeItem::buttons_count,
		&ModeItem::buttons_at,
		&ModeItem::buttons_clear
	);
}

void ModeItem::buttons_append(QQmlListProperty<ButtonItem> *property, ButtonItem *button)
{
	ModeItem *that = static_cast<ModeItem *>(property->object);
	button->setParentItem(that);
	that->m_buttons.append(button);
	if (that->m_layout) {
		that->m_layout->addButton(button);
	}
	QObject::connect(button, SIGNAL(symbolTriggered(const QString &)), that, SLOT(onSymbolTriggered(const QString &)));
}

int ModeItem::buttons_count(QQmlListProperty<ButtonItem> *property)
{
	ModeItem *that = static_cast<ModeItem *>(property->object);
	return that->m_buttons.count();
}

ButtonItem *ModeItem::buttons_at(QQmlListProperty<ButtonItem> *property, int idx)
{
	ModeItem *that = static_cast<ModeItem *>(property->object);
	return that->m_buttons.value(idx, 0);
}

void ModeItem::buttons_clear(QQmlListProperty<ButtonItem> *property)
{
	ModeItem *that = static_cast<ModeItem *>(property->object);
	if (that->m_layout) {
		that->m_layout->clearButtons();
	}
	foreach (ButtonItem *button, that->m_buttons) {
		QObject::disconnect(button, SIGNAL(symbolTriggered(const QString &)), that, SLOT(onSymbolTriggered(const QString &)));
		button->setParentItem(0);
	}
	that->m_buttons.clear();
}

void ModeItem::onSymbolTriggered(const QString &symbol)
{
}

