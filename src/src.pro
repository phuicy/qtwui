CONFIG += warn_on \
	  thread \
          qt \
	  dll \
	  debug
QT -= gui
TEMPLATE = lib

TARGET = QtWeb

DESTDIR = ../lib/

QT += core \
network \
xml
OBJECTS_DIR = .tmp/obj

UI_DIR = .tmp/ui

MOC_DIR = .tmp/moc

SOURCES += kernel/qwebtcpserver.cpp \
kernel/qwebfileressource.cpp \
kernel/qwebmessageressource.cpp \
kernel/qwebhttpserver.cpp \
kernel/qwebfcgidevice.cpp \
kernel/qwebapplicationfactory.cpp \
kernel/qwebparameters.cpp \
kernel/qwebapplication.cpp \
kernel/qwebapplicationserver.cpp \
kernel/qwebabstracthttpserver.cpp \
kernel/qwebbufferedressource.cpp \
kernel/qwebabstractressource.cpp \
kernel/qwebressourceproviderserver.cpp \
kernel/qwebhttpserverdelegate.cpp \
kernel/qwebabstractressourceproviderfactory.cpp \
kernel/qwebabstracthttpserverdelegate.cpp \
kernel/qwebfileressourceprovider.cpp \
kernel/qwebabstractressourceprovider.cpp \
webgets/qwebwebget.cpp \
webgets/qweblink.cpp \
webgets/qwebmainwebget.cpp
HEADERS += kernel/qwebhttpserverdelegate.h \
kernel/qwebabstractressourceproviderfactory.h \
kernel/qwebfcgidevice.h \
kernel/qwebapplicationcreator.h \
kernel/qwebtcpserver.h \
kernel/qwebabstracthttpserver.h \
kernel/qwebglobal.h \
kernel/qwebparameters.h \
kernel/qwebhttpserver.h \
kernel/qwebapplicationserver.h \
kernel/qwebmessageressource.h \
kernel/qwebfileressourceprovider.h \
kernel/qwebfileressource.h \
kernel/qwebapplicationfactory.h \
kernel/qwebabstractressource.h \
kernel/qwebressourceproviderserver.h \
kernel/qwebbufferedressource.h \
kernel/qwebabstracthttpserverdelegate.h \
kernel/qwebressourceproviderfactory.h \
kernel/qwebapplication.h \
kernel/qwebabstractressourceprovider.h \
webgets/qwebwebget.h \
webgets/qwebmainwebget.h \
webgets/qweblink.h
INSTALLS += target

target.path = ../bin
DISTFILES += ../javascript/qweblink.js \
../stylesheets/qtweb.css \
.
INCLUDEPATH += ../include

