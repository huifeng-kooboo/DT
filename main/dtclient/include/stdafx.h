#ifndef STDAFX_H
#define STDAFX_H

// C++自带
#include <set>

// QT 相关的头文件库
#include <QObject>
#include <QString>
#include <QVector>
#include <QFlag>
#include <QWidget>
#include <qnamespace.h>
#include <QMouseEvent>
#include <QFormLayout>
#include <QGridLayout>
#include <QLayout>
#include <QScreen>
#include <QTabWidget>
#include <QDebug>
#include <QProcess>
#include <QMessageBox>
#include <QMainWindow>
#include <QStatusBar>
#include <QListWidget>
#include <QSharedPointer>
#include <QApplication>
#include <QSettings>
#include <QTextCodec>
#include <QScreen>
#include <QHostInfo>

// Others
#include "../../global/define.h"

// 处理中文乱码使用
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif



#endif // STDAFX_H
