#ifndef COMMON_H
#define COMMON_H

#include <QMainWindow>

class CCommon{

public:
    /*
     * @brief: 获取主窗口的句柄
     *
     */
    static  QMainWindow*  getMainWindow();

    static void setDefaultCode();
};




#endif // COMMON_H
