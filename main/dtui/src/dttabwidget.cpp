#include "dttabwidget.h"


DTTabWidget::DTTabWidget(QWidget * pParent)
{
     setWindowFlag(Qt::FramelessWindowHint);
     //setAttribute(Qt::WA_TranslucentBackground, true);
     setAttribute(Qt::WA_StyledBackground,true);
     setFixedHeight(80);
     m_pLayout = new QHBoxLayout(this);
     setLayout(m_pLayout);
     //setStyleSheet("QWidget {background-color:#4de7f7;}");
};

DTTabWidget::~DTTabWidget()
{

}

void DTTabWidget::addTabByName(const QString &qsTabName, QIcon qIcon, QString qsObjectName, bool bShowTabName)
{
    QToolButton* toolBtn = new QToolButton(this);
    toolBtn->setText(qsTabName);
    //toolBtn->setIcon(qIcon);
    toolBtn->setObjectName(qsObjectName);
    toolBtn->setFixedSize(120,30);
    toolBtn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    if(!bShowTabName)
    {
        toolBtn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly); // 只展示Icon
    }
    m_pLayout->addWidget(toolBtn);
    m_pLayout->addSpacing(5);
    m_vecToolBtns.append(toolBtn);
}

void DTTabWidget::setCenterWidget(QWidget *widget)
{
    m_pLayout->addWidget(widget);
    m_pLayout->addSpacing(5);
}

QVector<QToolButton*> DTTabWidget::getToolButtonVec()
{
    return m_vecToolBtns;

}
