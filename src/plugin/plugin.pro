QT += qml quick gui-private
CONFIG += plugin

TARGET = quickkeyboard
TEMPLATE = lib
DESTDIR = ../../platforminputcontexts

DEFINES += QUICKKEYBOARD_LIBRARY

include($$PWD/../components.pri)

HEADERS += global.h \
	InputContextPlugin.h \
	InputContext.h
SOURCES += InputContextPlugin.cpp \
	InputContext.cpp

target.path = $$[QT_INSTALL_PLUGINS]/platforminputcontexts
INSTALLS += target
