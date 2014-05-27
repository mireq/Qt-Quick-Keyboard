#include <QGuiApplication>
#include <QQuickView>
#include <QUrl>

int main(int argc, char *argv[])
{
	qputenv("QUICKKEYBOARD_MAIN_FILE", "qrc:/keyboard.qml");
	QString libPath;
	{
		QCoreApplication a(argc, argv);
		QStringList path = QGuiApplication::applicationDirPath().split("/");
		path.pop_back();
		path.pop_back();
		libPath = path.join("/");
	}
	QGuiApplication::addLibraryPath(libPath);
	QGuiApplication app(argc, argv);
	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setSource(QUrl("qrc:/notepad.qml"));
	view.show();
	return app.exec();
}
