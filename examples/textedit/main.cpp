#include <QGuiApplication>
#include <QQuickView>
#include <QUrl>

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	app.addLibraryPath(app.applicationDirPath() + "/../../");
	QQuickView view;
	view.setSource(QUrl("qrc:/example.qml"));
	view.show();
	return app.exec();
}
