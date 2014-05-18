#include <QGuiApplication>
#include <QQuickView>
#include <QUrl>
#include "../../src/KeyboardItem.h"
#include "../../src/Dispatcher.h"
#include "../../src/ModeItem.h"
#include "../../src/ButtonItem.h"
#include "../../src/GridLayoutItem.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	qmlRegisterType<QuickKeyboard::KeyboardItem>("QuickKeyboard", 1, 0, "Keyboard");
	qmlRegisterType<QuickKeyboard::ModeItem>("QuickKeyboard", 1, 0, "Mode");
	qmlRegisterType<QuickKeyboard::ButtonItem>("QuickKeyboard", 1, 0, "Button");
	qmlRegisterType<QuickKeyboard::Dispatcher>("QuickKeyboard", 1, 0, "Dispatcher");
	qmlRegisterType<QuickKeyboard::LayoutItem>();
	qmlRegisterType<QuickKeyboard::GridLayoutItemAttached>();
	qmlRegisterType<QuickKeyboard::GridLayoutItem>("QuickKeyboard", 1, 0, "GridLayout");

	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setSource(QUrl("qrc:/keyboard.qml"));
	view.show();

	return app.exec();
}
