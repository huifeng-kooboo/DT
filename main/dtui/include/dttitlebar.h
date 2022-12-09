#ifndef DTTITLEBAR_H
#define DTTITLEBAR_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QToolButton>
#include "dtbutton.h"

// 标题栏
class DTTitleBar: public QWidget
{
    Q_OBJECT
public:
    explicit DTTitleBar(QWidget* parent = nullptr);
    ~DTTitleBar();

public:

    // 标题相关设置
    void setCurrentWindowTitle(const QString& qsTitle); // 设置标题

    /**
      * @brief: 预留设置标题接口 但是由于目前使用统一的StyleSheet 故不调用
    */
    void setTitleColor(const QColor& qc);  // 设置标题颜色
    void setTitleFont(const QFont& qFont); // 设置标题字体
    void setBackgroundColor(const QColor& qc);


    void homePageClick();
    void setCanStrech(bool bStrech) // 设置当前模式是否支持拉伸，默认支持
    {
            m_bStrech = bStrech;
    }
    bool getCanStrech()
    {
        return m_bStrech;
    }

    // 左侧Logo
    void setLogo(const QIcon& qIcon);

    // 设置最小化、最大化、关闭按钮的Icon
    void setButtonsIcon(const QIcon& qMinIcon,const QIcon& qMaxIcon,const QIcon& qCloseIcon,const QIcon& qMinHoverIcon,const QIcon& qMaxHoverIcon,const QIcon& qCloseHoverIcon,
                        const QIcon& qMinPressIcon,const QIcon& qMaxPressIcon,const QIcon& qClosePressIcon);

    // 设置主页Icon，Size
    void setHomePageIcon(const QIcon& qIcon,const QIcon&qHoverIcon,const QIcon&qPressIcon,const QSize& qSize);

    /**
     * @brief: 标题栏添加工具
     * @param: pBtn: 工具按钮
     */
    void addToolButton(QPushButton * pBtn);

    /**
     * @brief: 添加标题栏TabButton工具
     * @param: pBtn
     * @param: isNeedClose: 是否需要关闭按钮
     */
    void addTabButton(DTButton * pBtn,bool isNeedClose = false);

    bool isContainsTabButtons(const QString& ip);

    /**
      * @brief: 关闭Tab页
      * @param: ip: ip地址
     */
    bool closeTabByIp(const QString& ip);


public slots:
    void resizeEvent(QResizeEvent *event) override;
    void slotHomePageEvent();
    void slotCloseTab(QString);
    void slotTabBtnClicked(QAbstractButton* pBtn);

private:
    void initControls(); // 初始化控件


private:
    QPoint m_PointMouse; // 鼠标移动的位置
    QWidget * m_pParent;
    QLabel * m_pTitle; // 标题
    bool m_bStrech = true; //
    QToolButton * m_pLogoBtn; // Logo
    DTButton * m_pMinBtn; // 最小化按钮
    DTButton * m_pMaxBtn; // 最大化按钮
    DTButton * m_pCloseBtn; // 关闭按钮
    DTButton * m_pHomePageBtn; // 首页按钮

    QHBoxLayout* m_pBtnsHBoxLayout; // 关闭最小化按钮集合

    QVector<DTButton*> m_vecTabBtns; // tab按钮集合
    QHBoxLayout* m_pTabLayout; // Tab布局《----
    QButtonGroup * m_btn_group;

    /**
     * @brief:当前UI不需要（预留）---
    */
    QHBoxLayout* m_pToolsLayout; //工具Layout
    QVector<QPushButton*> m_vecToolBtns; // 工具按钮集合
};


#endif // DTCUSTOMTITLEWIDGET_H
