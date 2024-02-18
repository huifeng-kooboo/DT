#include "common.h"
#include <QApplication>

QMainWindow* CCommon::getMainWindow()
{
    foreach (QWidget *w, qApp->topLevelWidgets())
           if (QMainWindow* mainWin = qobject_cast<QMainWindow*>(w))
               return mainWin;
       return nullptr;
}

