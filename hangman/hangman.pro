TEMPLATE = app

DESTDIR = ../bin

INCLUDEPATH += ../src \
../include/
LIBS += -L../lib \
-lQtWui

unix:TARGETDEPS += ../lib/libQtWui.so
win32:TARGETDEPS += ../lib/QtWui.dll

MOC_DIR = .tmp/moc

OBJECTS_DIR = .tmp/obj

UI_DIR = .tmp/ui

SOURCES += main.cpp \
HangMan.cpp \
 Game.cpp
HEADERS += HangMan.h \
 Game.h

