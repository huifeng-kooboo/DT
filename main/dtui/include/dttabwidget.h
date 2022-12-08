#ifndef DTTABWIDGET_H
#define DTTABWIDGET_H
#include <QTabWidget>

/*
 * TabWidget界面重写
*/


class DTTabWidget: public QTabWidget
{
    Q_OBJECT
public:
    DTTabWidget(QWidget* pParent = nullptr);
    ~DTTabWidget();


    /*
     * @brief: 添加Tab页的基本信息
     * qsTabName: tab名称
     * qIcon: 图标
     * pWidget: 窗体
     * bShowTabName:是否展示Tab名称？展示tab名称：只展示图标
    */
    void addTabByName(const QString& qsTabName, QIcon qIcon, QWidget* pWidget,bool bShowTabName=true);

};


#endif // DTTABWIDGET_H
