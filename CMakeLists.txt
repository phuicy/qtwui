cmake_minimum_required(VERSION 2.8.11)

project(qtwui)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qt5Xml)



include_directories(
include
src
)

set(
interface_files
 include/QtWui/qwuiabstracthttpserver
 include/QtWui/qwuiabstracthttpserverdelegate.h
 include/QtWui/qwuiabstractresource.h
 include/QtWui/qwuiabstractresourceprovider.h
 include/QtWui/qwuiabstractresourceproviderfactory.h
 include/QtWui/qwuifcgidevice.h
 include/QtWui/qwuihttpheader.h
 include/QtWui/qwuihttpserver.h
 include/QtWui/qwuihttpserverdelegate.h
 include/QtWui/qwuimessageresource.h
 include/QtWui/qwuiresourceproviderfactory.h
 include/QtWui/qwuiresourceproviderserver.h
 include/QtWui/qwuitcpserver.h
 include/QtWui/qwuiapplication.h
 include/QtWui/qwuiapplicationcreator.h
 include/QtWui/qwuiapplicationfactory.h
 include/QtWui/qwuiapplicationserver.h
 include/QtWui/qwuiboxlayout.h
 include/QtWui/qwuibufferedresource.h
 include/QtWui/qwuifileresource.h
 include/QtWui/qwuifileresourceprovider.h
 include/QtWui/qwuiglobal.h
 include/QtWui/qwuigridlayout.h
 include/QtWui/qwuilayout.h
 include/QtWui/qwuilayoutitem.h
 include/QtWui/qwuiparameters.h
 include/QtWui/qwuistackedlayout.h
 include/QtWui/qwuitag.h
 include/QtWui/qwuilabel.h
 include/QtWui/qwuimainwebget.h
 include/QtWui/qwuiscrollarea.h
 include/QtWui/qwuistackedwebget.h
 include/QtWui/qwuiwebget.h
)

set(
hdr_files
 src/http/qwuiabstracthttpserver.h
 src/http/qwuiabstracthttpserverdelegate.h
 src/http/qwuiabstractresource.h
 src/http/qwuiabstractresourceprovider.h
 src/http/qwuiabstractresourceproviderfactory.h
 src/http/qwuifcgidevice.h
 src/http/qwuihttpheader.h
 src/http/qwuihttpserver.h
 src/http/qwuihttpserverdelegate.h
 src/http/qwuimessageresource.h
 src/http/qwuiresourceproviderfactory.h
 src/http/qwuiresourceproviderserver.h
 src/http/qwuitcpserver.h
 src/kernel/qwuiapplication.h
 src/kernel/qwuiapplicationcreator.h
 src/kernel/qwuiapplicationfactory.h
 src/kernel/qwuiapplicationserver.h
 src/kernel/qwuiboxlayout.h
 src/kernel/qwuibufferedresource.h
 src/kernel/qwuifileresource.h
 src/kernel/qwuifileresourceprovider.h
 src/kernel/qwuiglobal.h
 src/kernel/qwuigridlayout.h
 src/kernel/qwuilayout.h
 src/kernel/qwuilayoutitem.h
 src/kernel/qwuiparameters.h
 src/kernel/qwuistackedlayout.h
 src/kernel/qwuitag.h
 src/webgets/qwuilabel.h
 src/webgets/qwuimainwebget.h
 src/webgets/qwuiscrollarea.h
 src/webgets/qwuistackedwebget.h
 src/webgets/qwuiwebget.h
)

set(
src_files
 src/http/qwuiabstracthttpserver.cpp
 src/http/qwuiabstracthttpserverdelegate.cpp
 src/http/qwuiabstractresource.cpp
 src/http/qwuiabstractresourceprovider.cpp
 src/http/qwuiabstractresourceproviderfactory.cpp
 src/http/qwuifcgidevice.cpp
 src/http/qwuihttpheader.cpp
 src/http/qwuihttpserver.cpp
 src/http/qwuihttpserverdelegate.cpp
 src/http/qwuimessageresource.cpp
 src/http/qwuiresourceproviderserver.cpp
 src/http/qwuitcpserver.cpp
 src/kernel/qwuiapplication.cpp
 src/kernel/qwuiapplicationfactory.cpp
 src/kernel/qwuiapplicationserver.cpp
 src/kernel/qwuiboxlayout.cpp
 src/kernel/qwuibufferedresource.cpp
 src/kernel/qwuifileresource.cpp
 src/kernel/qwuifileresourceprovider.cpp
 src/kernel/qwuigridlayout.cpp
 src/kernel/qwuilayout.cpp
 src/kernel/qwuilayoutitem.cpp
 src/kernel/qwuiparameters.cpp
 src/kernel/qwuistackedlayout.cpp
 src/kernel/qwuitag.cpp
 src/webgets/qwuilabel.cpp
 src/webgets/qwuimainwebget.cpp
 src/webgets/qwuiscrollarea.cpp
 src/webgets/qwuistackedwebget.cpp
 src/webgets/qwuiwebget.cpp
)

# Tell CMake to create the helloworld executable
add_library(qtwui ${hdr_files} ${src_files} )

# Use the Widgets module from Qt 5.
target_link_libraries(qtwui Qt5::Widgets Qt5::Network Qt5::Xml)

set(hangman_file
hangman/Game.h
hangman/Game.cpp
hangman/HangMan.h
hangman/HangMan.cpp
)

add_executable(hangmain hangman/main.cpp ${hangman_file})
target_link_libraries(hangmain qtwui)

set(test_file
testapp/TestWebget.h
testapp/TestWebget.cpp
)

add_executable(test testapp/main.cpp ${test_file})
target_link_libraries(test qtwui)