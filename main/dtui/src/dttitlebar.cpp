#include "dttitlebar.h"
#include <QMouseEvent>
#include <QPalette>
#include "dt_stylesheets.h"

DTTitleBar::DTTitleBar(QWidget* parent)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(TITLE_BAR_STYLE);
    if(parent)
    {
        // 设置父窗体
        m_pParent = parent;
    }
    m_btn_group = new QButtonGroup(this);
    connect(m_btn_group,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slotTabBtnClicked(QAbstractButton*)));
    initControls();

}

DTTitleBar::~DTTitleBar()
{

}

void DTTitleBar::setTitleBarStyle(const QString &qsStyle)
{
    this->setStyleSheet(qsStyle);
}

void DTTitleBar::slotTabBtnClicked(QAbstractButton* pAbstractBtn)
{
    pAbstractBtn->setCheckable(true);
    pAbstractBtn->setChecked(true);
    if(pAbstractBtn!=m_pHomePageBtn)
    {
        pAbstractBtn->setIcon(QIcon(":/resources/camera_press.png"));
        m_pHomePageBtn->setIcon(QIcon(":/resources/homepage.png"));
    }
    else{
        m_pHomePageBtn->setIcon(QIcon(":/resources/homepage_press.png"));
    }
    for(auto btn: m_btn_group->buttons())
    {
        if(btn!=pAbstractBtn)
        {
            btn->setCheckable(true);
            btn->setChecked(false);
            if(btn!=m_pHomePageBtn)
            {
                btn->setIcon(QIcon(":/resources/camera.png"));
            }
        }
    }
}

void DTTitleBar::setCurrentWindowTitle(const QString& qsTitle)
{
    // 设置标题
    m_pTitle->setText(qsTitle);
}

void DTTitleBar::setBackgroundColor(const QColor& qc)
{
    QPalette qpa(this->palette());
    qpa.setColor(QPalette::Background,qc);
    this->setAutoFillBackground(true);
    this->setPalette(qpa);
    this->show();
}

void DTTitleBar::setTitleColor(const QColor& qc)
{
    QPalette pe;
    pe.setColor(QPalette::WindowText, qc);
    m_pTitle->setPalette(pe);
}

void DTTitleBar::setTitleFont(const QFont& qFont)
{
    m_pTitle->setFont(qFont);
}

void DTTitleBar::homePageClick()
{
    m_pHomePageBtn->click();
    m_pHomePageBtn->clicked();
}

void DTTitleBar::addToolButton(QPushButton* pBtn)
{
    m_vecToolBtns.append(pBtn);
    m_pToolsLayout->addWidget(pBtn);
}

bool DTTitleBar::closeTabByIp(const QString &ip)
{
    int i = -1;
    for(auto btn: m_vecTabBtns)
    {
        i++;
        if(btn->property("ip") == ip)
        {
            btn->setParent(NULL);
            m_pTabLayout->removeWidget(btn);
            m_btn_group->removeButton(btn);
            if(m_vecTabBtns.size() > 1 && i > 0)
            {
                m_vecTabBtns.at(i-1)->click();
                m_vecTabBtns.at(i-1)->clicked();
            }
            else{
                homePageClick();
            }
            break;
        }
    }
    m_vecTabBtns.removeAt(i);
    return true;
}

bool DTTitleBar::isContainsTabButtons(const QString &ip)
{
    for(auto btn: m_vecTabBtns)
    {
        if(btn->property("ip").toString() == ip)
        {
            btn->clicked();
            return true;
        }
    }
    return false;
}

void DTTitleBar::addTabButton(DTButton*pBtn, bool isNeedClose)
{
    if(m_vecTabBtns.contains(pBtn))
        return;
    pBtn->setAttribute(Qt::WA_StyledBackground, true);
    pBtn->setStyleSheet(TITLE_BAR_BUTTON_STYLE);
    pBtn->setCloseBtn(isNeedClose);
    pBtn->setFixedWidth(200);
    pBtn->setFixedHeight(44);
    pBtn->setFlat(0);
    connect(pBtn,SIGNAL(signalCloseTab(QString)),this,SLOT(slotCloseTab(QString)));
    m_vecTabBtns.append(pBtn);
    m_btn_group->addButton(pBtn);
    m_pTabLayout->addWidget(pBtn);
}

void DTTitleBar::slotCloseTab(QString qsTabName)
{
    int i = -1;
    for(auto btn: m_vecTabBtns)
    {
        i++;
        if(btn->objectName() == qsTabName)
        {
            btn->setParent(NULL);
            m_pTabLayout->removeWidget(btn);
            m_btn_group->removeButton(btn);
            if(m_vecTabBtns.size() > 1 && i > 0)
            {
                m_vecTabBtns.at(i-1)->click();
                m_vecTabBtns.at(i-1)->clicked();
            }
            else{
                homePageClick();
            }
            break;
        }
    }
    m_vecTabBtns.removeAt(i);
}

void DTTitleBar::resizeEvent(QResizeEvent *event)
{

}

void DTTitleBar::initControls()
{
    m_pBtnsHBoxLayout = new QHBoxLayout(this);
    m_pBtnsHBoxLayout->setMargin(0);
    m_pBtnsHBoxLayout->setContentsMargins(0,0,0,0);
    this->setLayout(m_pBtnsHBoxLayout);
    /*
     * 暂时不需要Tool功能 故屏蔽
    */
    // m_pToolsLayout = new QHBoxLayout(this);
    m_pTabLayout = new QHBoxLayout(this);
    m_pTabLayout->setMargin(0);
    m_pTabLayout->setContentsMargins(0,0,0,0);
    m_pTitle = new QLabel(this);
    m_pTitle->setMinimumWidth(130);
    m_pTitle->setObjectName("window_title");

    // Logo按钮
    m_pLogoBtn = new QToolButton(this);
    m_pLogoBtn->setObjectName("window_logo");
    m_pLogoBtn->setAttribute(Qt::WA_StyledBackground, true);

    /**
      * @brief: Logo和标题添加
    */
    m_pBtnsHBoxLayout->addWidget(m_pLogoBtn,0,Qt::AlignLeft);
    m_pBtnsHBoxLayout->addWidget(m_pTitle,0,Qt::AlignLeft);

    /**
      * @brief: 首页按钮
    */
    m_pHomePageBtn = new DTButton(this);
    m_pHomePageBtn->setObjectName("win_homepage");
    m_pHomePageBtn->setStyleSheet(TITLE_BAR_BUTTON_STYLE);
    m_btn_group->addButton(m_pHomePageBtn);
    m_pBtnsHBoxLayout->addWidget(m_pHomePageBtn,0,Qt::AlignLeft);

    m_pBtnsHBoxLayout->addLayout(m_pTabLayout);

    // 关闭 最小化 最大化按钮
    m_pMinBtn = new DTButton(this);
    m_pMinBtn->setObjectName("window_min");
    m_pMinBtn->setFlat(true);
    m_pMinBtn->setStyleSheet(TITLE_BAR_BUTTON_STYLE);

    m_pMaxBtn = new DTButton(this);
    m_pMaxBtn->setObjectName("window_max");
    m_pMaxBtn->setFlat(true);
    m_pMaxBtn->setStyleSheet(TITLE_BAR_BUTTON_STYLE);

    m_pCloseBtn = new DTButton(this);
    m_pCloseBtn->setObjectName("window_close");
    m_pCloseBtn->setFlat(true);
    m_pCloseBtn->setStyleSheet(TITLE_BAR_BUTTON_STYLE);

    // 绑定相关的事件
    connect(m_pMinBtn,SIGNAL(clicked()),m_pParent,SLOT(slotMinEvent()));
    connect(m_pMaxBtn,SIGNAL(clicked()),m_pParent,SLOT(slotMaxEvent()));
    connect(m_pCloseBtn,SIGNAL(clicked()),m_pParent,SLOT(slotCloseEvent()));
    connect(m_pHomePageBtn,SIGNAL(clicked()),m_pParent,SLOT(slotHomePageEvent()));
    connect(m_pHomePageBtn,SIGNAL(clicked()),this,SLOT(slotHomePageEvent()));

    m_pBtnsHBoxLayout->addStretch();

    /**
      * @brief: 添加最大化、最小化、正常按钮
    */
    m_pBtnsHBoxLayout->addWidget(m_pMinBtn,0,Qt::AlignRight);
    m_pBtnsHBoxLayout->addWidget(m_pMaxBtn,0,Qt::AlignRight);
    m_pBtnsHBoxLayout->addWidget(m_pCloseBtn,0,Qt::AlignRight);
    m_pBtnsHBoxLayout->addSpacing(5);
}

void DTTitleBar::setLogo(const QIcon& qIcon)
{
    m_pLogoBtn->setIcon(qIcon);
    m_pLogoBtn->setIconSize(QSize(32,18));
    m_pLogoBtn->setFixedSize(QSize(56,44));
    m_pLogoBtn->setGeometry(0,0,56,44);
}

void DTTitleBar::setButtonsIcon(const QIcon &qMinIcon, const QIcon &qMaxIcon, const QIcon &qCloseIcon, const QIcon &qMinHoverIcon, const QIcon &qMaxHoverIcon, const QIcon &qCloseHoverIcon, const QIcon &qMinPressIcon, const QIcon &qMaxPressIcon, const QIcon &qClosePressIcon)
{
    m_pMinBtn->setFixedHeight(44);
    m_pMaxBtn->setFixedHeight(44);
    m_pCloseBtn->setFixedHeight(44);
    m_pMinBtn->setFixedWidth(36);
    m_pMaxBtn->setFixedWidth(36);
    m_pCloseBtn->setFixedWidth(36);
    m_pMinBtn->setIcon(qMinIcon);
    m_pMaxBtn->setIcon(qMaxIcon);
    m_pCloseBtn->setIcon(qCloseIcon);

    m_pMinBtn->setStateIcon(qMinIcon,qMinHoverIcon,qMinPressIcon);
    m_pMaxBtn->setStateIcon(qMaxIcon,qMaxHoverIcon,qMaxPressIcon);
    m_pCloseBtn->setStateIcon(qCloseIcon,qCloseHoverIcon,qClosePressIcon);

    m_pMinBtn->setIconSize(QSize(16,16));
    m_pMaxBtn->setIconSize(QSize(16,16));
    m_pCloseBtn->setIconSize(QSize(16,16));
}

void DTTitleBar::setHomePageIcon(const QIcon& qIcon,const QIcon&qHoverIcon,const QIcon&qPressIcon,const QSize& qSize)
{
    m_pHomePageBtn->setIcon(qIcon);
    m_pHomePageBtn->setIconSize(qSize);
    m_pHomePageBtn->setBtnFixedSize(QSize(60,44));
    m_pHomePageBtn->setFlat(true);
}

void DTTitleBar::slotHomePageEvent()
{
    //
}
