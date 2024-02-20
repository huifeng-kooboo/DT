include (../main.pri)

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = lib
CONFIG += staticlib

# 添加预编译头文件
CONFIG += PRECOMPILED_HEADER
PRECOMPILED_HEADER =  $$PWD/include/stdafx.h

#
DESTDIR = $$PWD/../../bin/
TARGET = dtui
#
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

SOURCES += \
    src/dtbutton.cpp \
    src/dtcheckbox.cpp \
    src/dtgraphicsitem.cpp \
    src/dtgraphicsscene.cpp \
    src/dtgraphicstool.cpp \
    src/dtgraphicsview.cpp \
    src/dtgroupbox.cpp \
    src/dtlabel.cpp \
    src/dtpainter.cpp \
    src/dtprogressbar.cpp \
    src/dtrangeslider.cpp \
    src/dtscrollbar.cpp \
    src/dttabwidget.cpp \
    src/dttitlebar.cpp \
    src/dttoolbar.cpp \
    src/dttoolset.cpp \
    src/dtui.cpp \
    src/sizehandle.cpp

HEADERS += \
    include/dt_stylesheets.h \
    include/dtbutton.h \
    include/dtcheckbox.h \
    include/dtframelesswidget.h \
    include/dtgraphicsitem.h \
    include/dtgraphicsscene.h \
    include/dtgraphicstool.h \
    include/dtgraphicsview.h \
    include/dtgroupbox.h \
    include/dtlabel.h \
    include/dtpainter.h \
    include/dtprogressbar.h \
    include/dtrangeslider.h \
    include/dtscrollbar.h \
    include/dttabwidget.h \
    include/dttitlebar.h \
    include/dttoolbar.h \
    include/dttoolset.h \
    include/dtui.h \
    include/dtundocommand.h \
    include/sizehandle.h \
    include/stdafx.h

INCLUDEPATH +=\
    include \
    src \

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
