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

SOURCES += kernel/QWebAbstractRessourceProvider.cpp \
kernel/QWebApplication.cpp \
kernel/QWebFileRessourceProvider.cpp \
kernel/QWebHttpServer.cpp \
kernel/QWebAbstractHttpServer.cpp \
kernel/QWebAbstractRessource.cpp \
kernel/QWebAbstractRessourceProviderFactory.cpp \
kernel/QWebApplicationFactory.cpp \
kernel/QWebApplicationServer.cpp \
kernel/QWebBufferedRessource.cpp \
kernel/QWebFcgiDevice.cpp \
kernel/QWebFileRessource.cpp \
kernel/QWebMessageRessource.cpp \
kernel/QWebRessourceProviderServer.cpp \
kernel/QWebTcpServer.cpp \
kernel/QWebHttpServerDelegate.cpp \
kernel/QWebAbstractHttpServerDelegate.cpp \
webgets/QWebLink.cpp \
webgets/QWebMainWebget.cpp \
webgets/QWebWebget.cpp \
kernel/QWebParameters.cpp
HEADERS += kernel/QWebAbstractRessourceProvider.h \
kernel/QWebApplication.h \
kernel/QWebFileRessourceProvider.h \
kernel/QWebGlobal.h \
kernel/QWebHttpServer.h \
kernel/QWebAbstractHttpServer.h \
kernel/QWebAbstractRessource.h \
kernel/QWebAbstractRessourceProviderFactory.h \
kernel/QWebApplicationCreator.h \
kernel/QWebApplicationFactory.h \
kernel/QWebApplicationServer.h \
kernel/QWebBufferedRessource.h \
kernel/QWebFcgiDevice.h \
kernel/QWebFileRessource.h \
kernel/QWebMessageRessource.h \
kernel/QWebParameters.h \
kernel/QWebRessourceProviderFactory.h \
kernel/QWebRessourceProviderServer.h \
kernel/QWebTcpServer.h \
kernel/QWebHttpServerDelegate.h \
kernel/QWebAbstractHttpServerDelegate.h \
webgets/QWebLink.h \
webgets/QWebMainWebget.h \
webgets/QWebWebget.h
INSTALLS += target

target.path = ../bin
DISTFILES += ../javascript/qweblink.js \
../stylesheets/qtweb.css \
.
INCLUDEPATH += webgets \
kernel
