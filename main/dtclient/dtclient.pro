include (../main.pri)
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# 生成目标程序名称： 例如dtdt.exe
TARGET = dtdt


# 添加预编译头文件
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
    src/main.cpp \
    src/mainwindow.cpp \
    src/pluginsmanager.cpp \
    src/util.cpp

HEADERS += \
    include/util.h \
    include/win/dumper.h \
    include/globaldefine.h \
    include/mainwindow.h \
    include/pluginsmanager.h \
    include/stdafx.h \
    ../../global/define.h \

FORMS += \
    ui/about.ui \
    ui/mainwindow.ui

INCLUDEPATH += \
     include \
     src \

# 生成目录设置
DESTDIR = $$PWD/../../bin/

win32::LIBS += -L../../bin \
               -lcommon \

win32::LIBS += -L../../bin \
               -ldtui \

# 拷贝文件function
defineTest(copyToDestDir) {
    files = $$1
    dir = $$2
    # replace slashes in destination path for Windows
    win32:dir ~= s,/,\\,g

    for(file, files) {
        # replace slashes in source path for Windows
        win32:file ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$shell_quote($$file) $$shell_quote($$dir) $$escape_expand(\\n\\t)
    }
    export(QMAKE_POST_LINK)
}

# 拷贝文件 plugin.json拷贝到安装的目录
PLUGIN_INFO_FILES += \
    $$PWD/../../allplugins/plugins.json


copyToDestDir($$PLUGIN_INFO_FILES, $$PWD/../../bin/plugins)

# 复制编译打包的相关依赖
DEPEND_CORE_FILES += \
    ##-----windows环境相关的------
    $$PWD/../../depends/msvcp140.dll \
    $$PWD/../../depends/ucrtbase.dll \
    $$PWD/../../depends/vcruntime140.dll \
    ##------------Qt相关的-----------
    $$PWD/../../depends/Qt5Network.dll \

copyToDestDir($$DEPEND_CORE_FILES, $$PWD/../../bin)


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    dtclient.qrc
RC_ICONS = resources/icon.ico
