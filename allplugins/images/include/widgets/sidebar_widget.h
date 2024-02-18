#ifndef SIDEBAR_WIDGET_H
#define SIDEBAR_WIDGET_H

/**
  * @brief: 侧边栏
  *
*/
class SideBarWidget: public QWidget{
public:
    SideBarWidget(QWidget* pParent);
    ~SideBarWidget();

private:
    void init();
    void initData();
    void initStyle();

private:
    QVBoxLayout * m_pVBoxLayout;

};

#endif // SIDEBAR_WIDGET_H
