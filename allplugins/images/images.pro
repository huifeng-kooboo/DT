include (../../main/main.pri)
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
DEFINES += Images_LIBRARY

# 生成文件路径
DESTDIR = $$PWD/../../bin/plugins/
TARGET = images

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=\
    include \
    src \
    ../plugins_base \

SOURCES += \
    src/images.cpp


HEADERS += \
    include/images_global.h \
    include/images.h \
    ../plugins_base/pluginsmanager_base.h \

LIBS += $$PWD/../../bin/libcommon.a
LIBS += $$PWD/../../bin/libdtui.a
#LIBS += $$PWD/../../senseinsight/lib/windows/jsoncpp.lib
#LIBS += $$PWD/../../senseinsight/lib/windows/dllrpc_client.lib
#LIBS += $$PWD/../../senseinsight/lib/windows/CobraImageProcess.lib
#LIBS += $$PWD/../../senseinsight/lib/windows/dllvision_core.lib
#LIBS += $$PWD/../../senseinsight/lib/windows/SenseCommon.lib
#LIBS += $$PWD/../../senseinsight/lib/windows/CobraClassifyElDll.lib

## 集成common组件
#win32::LIBS += -L../../bin \
#               -lcommon \

## 集成ui组件
#win32::LIBS += -L../../bin \
#               -ldtui \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
