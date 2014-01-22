#include <QGuiApplication>
#include <QQuickView>
#include <QUrl>
#include "../../src/KeyboardItem.h"
#include "../../src/ModeItem.h"
#include "../../src/ButtonItem.h"
#include "../../src/GridLayoutItem.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	qmlRegisterType<KeyboardItem>("QuickKeyboard", 1, 0, "Keyboard");
	qmlRegisterType<ModeItem>("QuickKeyboard", 1, 0, "Mode");
	qmlRegisterType<ButtonItem>("QuickKeyboard", 1, 0, "Button");
	qmlRegisterType<LayoutItem>();
	qmlRegisterType<GridLayoutItemAttached>();
	qmlRegisterType<GridLayoutItem>("QuickKeyboard", 1, 0, "GridLayout");

	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setSource(QUrl("qrc:/keyboard.qml"));
	view.show();

	return app.exec();
}
