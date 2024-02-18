#ifndef DTTABWIDGET_H
#define DTTABWIDGET_H
#include <QTabWidget>
#include <QToolButton>
#include <QHBoxLayout>

/*
 * TabWidget界面重写
*/


class DTTabWidget: public QWidget
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
    void addTabByName(const QString& qsTitle, QIcon qIcon, QString qsObjectName,bool bShowTabName=true);

    /*
     * @brief: 设置中间的窗体
     */
    void setCenterWidget(QWidget* widget);

    QVector<QToolButton*> getToolButtonVec();

private:
    QVector<QToolButton*> m_vecToolBtns; // 工具集合
    QHBoxLayout * m_pLayout;

};


#endif // DTTABWIDGET_H
