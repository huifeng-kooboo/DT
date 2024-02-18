#include "dtgroupbox.h"
#include <QMouseEvent>
#include <QPalette>
#include "dt_stylesheets.h"
#include <QHBoxLayout>

// 处理中文乱码使用
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

DTGroupBox::DTGroupBox(QWidget* parent):QWidget(parent)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground,true);
    if(parent)
    {
        m_pParent = parent;
    }
    pVBoxLayout = new QVBoxLayout(this);
    QHBoxLayout * pCloseLayout = new QHBoxLayout();
    pVBoxLayout->addLayout(pCloseLayout);
    pVBoxLayout->addStretch();
    m_pTitle = new QLabel();
    m_pTitle->setObjectName("win_control_title");
    m_pCloseBtn = new QPushButton(this);
    m_pCloseBtn->setFixedSize(22,22);
    m_pCloseBtn->setObjectName("window_nor_close");
    m_pCloseBtn->setFocusPolicy(Qt::NoFocus);
    pCloseLayout->addSpacing(10);
    pCloseLayout->addWidget(m_pTitle);
    pCloseLayout->addStretch();
    pCloseLayout->addWidget(m_pCloseBtn);
    // 隐藏当前的界面
    connect(m_pCloseBtn,&QPushButton::clicked,[=](bool isChecked){
        this->hide();
    });
}

DTGroupBox::~DTGroupBox()
{

}

void DTGroupBox::setTitle(QString &qsTitle)
{
    m_pTitle->setText(qsTitle);
}

void DTGroupBox::setContentWidget(QWidget *contentWidget)
{
    pVBoxLayout->addWidget(contentWidget);
}
