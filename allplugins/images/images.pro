include (../../main/main.pri)
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
DEFINES += Images_LIBRARY

# 生成文件路径
DESTDIR = $$PWD/../../bin/plugins/

# 生成文件名称: ex: images: 生成文件名为:images.exe [WIN]
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

# 添加预编译头文件
CONFIG += PRECOMPILED_HEADER
PRECOMPILED_HEADER =  $$PWD/include/stdafx.h


# 引入文件部分

INCLUDEPATH +=\
    include \
    src \
    ../plugins_base \

SOURCES += \
    src/images.cpp \
    src/widgets/account_widget.cpp \
    src/widgets/sidebar_widget.cpp


HEADERS += \
    include/images_global.h \
    include/images.h \
    ../plugins_base/pluginsmanager_base.h \
    include/stdafx.h \
    include/widgets/account_widget.h \
    include/widgets/sidebar_widget.h

# Resource部分

RESOURCES += \
    images.qrc


# 添加依赖的静态库
win32::LIBS += $$PWD/../../bin/common.lib
win32::LIBS += $$PWD/../../bin/dtui.lib


# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


