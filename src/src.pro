CONFIG += warn_on \
	  thread \
          qt \
	  dll \
	  debug
QT -= gui
TEMPLATE = lib

TARGET = QtWeb

DESTDIR = ../lib/

system(../scripts/create-include-files.rb)

QT += core \
network \
xml
OBJECTS_DIR = .tmp/obj

UI_DIR = .tmp/ui

MOC_DIR = .tmp/moc

SOURCES += \
http/qwebmessageressource.cpp \
http/qwebabstracthttpserverdelegate.cpp \
http/qwebfcgidevice.cpp \
http/qwebabstracthttpserver.cpp \
http/qwebabstractressource.cpp \
http/qwebhttpserverdelegate.cpp \
http/qwebabstractressourceproviderfactory.cpp \
http/qwebhttpserver.cpp \
http/qwebabstractressourceprovider.cpp \
http/qwebressourceproviderserver.cpp \
http/qwebtcpserver.cpp \
kernel/qwebfileressourceprovider.cpp \
kernel/qwebapplicationserver.cpp \
kernel/qwebapplicationfactory.cpp \
kernel/qwebparameters.cpp \
kernel/qwebapplication.cpp \
kernel/qwebfileressource.cpp \
kernel/qwebbufferedressource.cpp \
kernel/qweblayout.cpp \
kernel/qwebboxlayout.cpp \
kernel/qweblayoutitem.cpp \
kernel/qwebgridlayout.cpp \
kernel/qwebtag.cpp \
kernel/qwebstackedlayout.cpp \
webgets/qweblabel.cpp \
webgets/qwebmainwebget.cpp \
webgets/qwebwebget.cpp \
webgets/qwebstackedwebget.cpp

HEADERS += http/qwebressourceproviderserver.h \
http/qwebressourceproviderfactory.h \
http/qwebtcpserver.h \
http/qwebmessageressource.h \
http/qwebabstracthttpserverdelegate.h \
http/qwebfcgidevice.h \
http/qwebabstracthttpserver.h \
http/qwebabstractressource.h \
http/qwebhttpserverdelegate.h \
http/qwebabstractressourceproviderfactory.h \
http/qwebhttpserver.h \
http/qwebabstractressourceprovider.h \
kernel/qwebfileressource.h \
kernel/qwebbufferedressource.h \
kernel/qwebapplicationcreator.h \
kernel/qwebfileressourceprovider.h \
kernel/qwebapplicationserver.h \
kernel/qwebapplicationfactory.h \
kernel/qwebglobal.h \
kernel/qwebparameters.h \
kernel/qwebapplication.h \
kernel/qweblayout.h \
kernel/qwebboxlayout.h \
kernel/qwebgridlayout.h \
kernel/qweblayoutitem.h \
kernel/qwebstackedlayout.h \
kernel/qwebtag.h \
webgets/qweblabel.h \
webgets/qwebwebget.h \
webgets/qwebmainwebget.h \
webgets/qwebstackedwebget.h

INSTALLS += target

target.path = ../bin
DISTFILES += ../javascript/qweblink.js \
../javascript/qtweb.js \
../stylesheets/qtweb.css \
../stylesheets/qwebmainwebget.css \
../stylesheets/qwebwebget.css \
../stylesheets/qweblabel.css

INCLUDEPATH += ../include
