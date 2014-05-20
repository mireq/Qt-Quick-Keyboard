QT += qml quick gui-private
CONFIG += plugin

TARGET = quickkeyboard
TEMPLATE = lib
DESTDIR = ../../platforminputcontexts

DEFINES += QUICKKEYBOARD_LIBRARY

include($$PWD/../components.pri)

HEADERS += global.h \
	InputContextEmbedded.h \
	InputContextPlugin.h \
	InputContext.h
SOURCES += InputContextEmbedded.cpp \
	InputContextPlugin.cpp \
	InputContext.cpp
RESOURCES += resources.qrc

target.path = $$[QT_INSTALL_PLUGINS]/platforminputcontexts
INSTALLS += target
