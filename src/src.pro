CONFIG += warn_on \
	  thread \
          qt \
	  dll \
	  debug
QT -= gui
TEMPLATE = lib

TARGET = QtWui

DESTDIR = ../lib/

system(../scripts/create-include-files.rb)

QT += core \
network \
xml
OBJECTS_DIR = .tmp/obj

UI_DIR = .tmp/ui

MOC_DIR = .tmp/moc

SOURCES += \
http/qwuimessageressource.cpp \
http/qwuiabstracthttpserverdelegate.cpp \
http/qwuifcgidevice.cpp \
http/qwuiabstracthttpserver.cpp \
http/qwuiabstractressource.cpp \
http/qwuihttpserverdelegate.cpp \
http/qwuiabstractressourceproviderfactory.cpp \
http/qwuihttpserver.cpp \
http/qwuiabstractressourceprovider.cpp \
http/qwuiressourceproviderserver.cpp \
http/qwuitcpserver.cpp \
kernel/qwuifileressourceprovider.cpp \
kernel/qwuiapplicationserver.cpp \
kernel/qwuiapplicationfactory.cpp \
kernel/qwuiparameters.cpp \
kernel/qwuiapplication.cpp \
kernel/qwuifileressource.cpp \
kernel/qwuibufferedressource.cpp \
kernel/qwuilayout.cpp \
kernel/qwuiboxlayout.cpp \
kernel/qwuilayoutitem.cpp \
kernel/qwuigridlayout.cpp \
kernel/qwuitag.cpp \
kernel/qwuistackedlayout.cpp \
webgets/qwuilabel.cpp \
webgets/qwuimainwebget.cpp \
webgets/qwuiwebget.cpp \
webgets/qwuistackedwebget.cpp

HEADERS += http/qwuiressourceproviderserver.h \
http/qwuiressourceproviderfactory.h \
http/qwuitcpserver.h \
http/qwuimessageressource.h \
http/qwuiabstracthttpserverdelegate.h \
http/qwuifcgidevice.h \
http/qwuiabstracthttpserver.h \
http/qwuiabstractressource.h \
http/qwuihttpserverdelegate.h \
http/qwuiabstractressourceproviderfactory.h \
http/qwuihttpserver.h \
http/qwuiabstractressourceprovider.h \
kernel/qwuifileressource.h \
kernel/qwuibufferedressource.h \
kernel/qwuiapplicationcreator.h \
kernel/qwuifileressourceprovider.h \
kernel/qwuiapplicationserver.h \
kernel/qwuiapplicationfactory.h \
kernel/qwuiglobal.h \
kernel/qwuiparameters.h \
kernel/qwuiapplication.h \
kernel/qwuilayout.h \
kernel/qwuiboxlayout.h \
kernel/qwuigridlayout.h \
kernel/qwuilayoutitem.h \
kernel/qwuistackedlayout.h \
kernel/qwuitag.h \
webgets/qwuilabel.h \
webgets/qwuiwebget.h \
webgets/qwuimainwebget.h \
webgets/qwuistackedwebget.h

INSTALLS += target

target.path = ../bin
DISTFILES += ../javascript/qwuilink.js \
../javascript/qtwui.js \
../stylesheets/qtwui.css \
../stylesheets/qwuimainwebget.css \
../stylesheets/qwuiwebget.css \
../stylesheets/qwuilabel.css

INCLUDEPATH += ../include
