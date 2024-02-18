#include "dttitlebar.h"
#include <QMouseEvent>
#include <QPalette>
#include "dt_stylesheets.h"

// 处理中文乱码使用
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

DTTitleBar::DTTitleBar(QWidget* parent):QWidget(parent)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground,true);
    if(parent)
    {
        m_pParent = parent;
    }
    initControls();
}

DTTitleBar::~DTTitleBar()
{

}

void DTTitleBar::setTitleBarStyle(const QString &qsStyle)
{
    this->setStyleSheet(qsStyle);
}

void DTTitleBar::setTitle(const QString &qsTitle)
{
    pTitleLabel->setText(qsTitle);
}

void DTTitleBar::addTextLabel(QLabel *qsText, int nPos)
{
    if(nPos ==0)
    {
        m_pLeftHBoxLayout->addWidget(qsText);
    }
    else{
        m_pRightHBoxLayout->addWidget(qsText);
    }
    m_pRightHBoxLayout->addSpacing(2);
}

void DTTitleBar::setRegion(const QString &qsRegion)
{
    pRegionLabel->setText(qsRegion);
}

void DTTitleBar::resizeEvent(QResizeEvent *event)
{

}

void DTTitleBar::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void DTTitleBar::initControls()
{
    m_pLeftHBoxLayout = new QHBoxLayout();
    m_pLeftHBoxLayout->setMargin(0);
    m_pLeftHBoxLayout->setContentsMargins(0,0,0,0);
    m_pRightHBoxLayout = new QHBoxLayout();
    m_pRightHBoxLayout->setMargin(0);
    m_pRightHBoxLayout->setContentsMargins(0,0,0,0);
    m_pBtnsHBoxLayout = new QHBoxLayout(this);
    m_pBtnsHBoxLayout->setMargin(0);
    m_pBtnsHBoxLayout->setContentsMargins(0,0,0,0);
    this->setLayout(m_pBtnsHBoxLayout);

    m_pTitleWidget = new QWidget(this);
    m_pTitleWidget->setObjectName("window_title_widget");
    m_pTitleWidget->setFixedSize(636,98);
    pTitleLabel = new QLabel(m_pTitleWidget);
    pTitleLabel->setObjectName("win_title");
    pTitleLabel->setGeometry(250,-10,400,68);

    pRegionLabel = new QLabel(m_pTitleWidget);
    pRegionLabel->setObjectName("win_region");
    pRegionLabel->setGeometry(296,53,400,30);
    m_pBtnsHBoxLayout->addStretch();
    m_pBtnsHBoxLayout->addLayout(m_pLeftHBoxLayout);
    m_pBtnsHBoxLayout->addWidget(m_pTitleWidget);
    m_pBtnsHBoxLayout->addLayout(m_pRightHBoxLayout);

    m_pCloseBtn = new QPushButton(this);
    m_pCloseBtn->setFixedSize(36,32);
    m_pCloseBtn->setObjectName("window_close");
    m_pCloseBtn->setFocusPolicy(Qt::NoFocus);
    m_pCloseBtn->setToolTip(tr("关闭"));

    connect(m_pCloseBtn,SIGNAL(clicked()),m_pParent,SLOT(slotCloseEvent()));
    m_pBtnsHBoxLayout->addStretch();
    QVBoxLayout *pCloseLayout = new QVBoxLayout(this);
    pCloseLayout->addSpacing(14);
    pCloseLayout->addWidget(m_pCloseBtn);
    pCloseLayout->addStretch();
    m_pBtnsHBoxLayout->addLayout(pCloseLayout);
    m_pBtnsHBoxLayout->addSpacing(7);
}

