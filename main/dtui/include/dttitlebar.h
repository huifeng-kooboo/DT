#ifndef DTTITLEBAR_H
#define DTTITLEBAR_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QToolButton>
#include "dtbutton.h"

/**
  * @brief: 标题栏基类
*/
class DTTitleBar: public QWidget
{
    Q_OBJECT
public:
    explicit DTTitleBar(QWidget* parent = nullptr);
    ~DTTitleBar();



public:

    /**
      * @brief: 设置标题栏的样式
      */
    void setTitleBarStyle(const QString& qsStyle);

    void setTitle(const QString& qsTitle); // 设置标题
    void setRegion(const QString& qsRegion); // 设置区域

    void addTextLabel(QLabel* qsText, int nPos=0); // 添加文本 nPos: 0:左边 1:右边


public slots:
    void resizeEvent(QResizeEvent *event) override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void initControls(); // 初始化控件


private:
    QWidget * m_pParent;  // 父窗体
    QPushButton * m_pCloseBtn; // 关闭按钮
    QHBoxLayout* m_pBtnsHBoxLayout; // 按钮集合
    QWidget* m_pTitleWidget; // 内嵌titleWidget
    QLabel* pTitleLabel; // 标题字段
    QLabel* pRegionLabel; // 区域字段

    QHBoxLayout* m_pLeftHBoxLayout; // Left Layout
    QHBoxLayout* m_pRightHBoxLayout; // 按钮集合
};


#endif // DTCUSTOMTITLEWIDGET_H
