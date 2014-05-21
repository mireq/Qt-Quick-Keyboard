#include <QGuiApplication>
#include <QQuickView>
#include <QUrl>
#include "../../src/register.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	registerQmlTypes();
	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setSource(QUrl("qrc:/keyboard.qml"));
	view.show();

	return app.exec();
}
