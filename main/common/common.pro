include (../main.pri)

# 默认QT版本5.14.2 【原因： 开源的最新版本】
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = $$PWD/../../bin/
TARGET = common

TEMPLATE = lib
DEFINES += COMMON_LIBRARY

CONFIG += c++14
CONFIG += staticlib
CONFIG += PRECOMPILED_HEADER
PRECOMPILED_HEADER =  $$PWD/include/stdafx.h

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/common.cpp \
    src/dtfile.cpp \
    src/dtimages.cpp \
    src/dtjson.cpp \
    src/dtlog.cpp \
    src/dtregistry.cpp \
    src/dttime.cpp

HEADERS += \
    include/common.h \
    include/dterrorcode.h \
    include/dtfile.h \
    include/dtimages.h \
    include/dtjson.h \
    include/dtlog.h \
    include/dtregistry.h \
    include/dttime.h \
    include/stdafx.h

INCLUDEPATH +=\
    include \
    src \



# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
