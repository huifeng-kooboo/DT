#include "dttoolbar.h"
#include "dt_stylesheets.h"
#include <QFrame>
#include <QDebug>
#pragma execution_character_set("utf-8")

DTToolBar::DTToolBar(QWidget* parent)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground, true);
    m_pBtnsLayout = new QHBoxLayout(this);
    m_pBtnsLayout->setMargin(0);
    m_pBtnsLayout->setContentsMargins(0,0,0,0);
    m_pBtnsLayout->setGeometry(QRect(QPoint(0,0),QSize(this->width(),this->height())));
    m_pToolsLayout = new QHBoxLayout(this);
    m_pToolsLayout->setMargin(0);
    m_pToolsLayout->setContentsMargins(0,0,0,0);
    m_pBtnsLayout->addStretch();
    m_pBtnsLayout->addLayout(m_pToolsLayout);
    m_pBtnsLayout->addStretch();
    this->setLayout(m_pBtnsLayout);
}

DTToolBar::~DTToolBar()
{

}

// 工具栏增加工具
void DTToolBar::addTool(const QString &qsToolName, QIcon qIcon, QPushButton* btn, Qt::Alignment align)
{
    //todo
    m_vecBtns.append(btn);
    btn->setAttribute(Qt::WA_StyledBackground, true);
    btn->setIcon(qIcon);
    btn->setIconSize(QSize(16,16));
    btn->setStyleSheet(TOOL_BUTTON_STYLE);
    btn->setChecked(btn->isChecked()?true:false);
    m_pToolsLayout->addWidget(btn,0,align);
}

void DTToolBar::slotActivated(const QString& qsActivated)
{
}

void DTToolBar::setBackgroundColor(const QColor& qc)
{
    QPalette qpa(this->palette());
    qpa.setColor(QPalette::Background,qc);
    this->setAutoFillBackground(true);
    this->setPalette(qpa);
    this->show();
}

void DTToolBar::addSplitLine()
{
    QFrame* line = new QFrame(nullptr);
    line->setFixedHeight(16);
    line->setFixedWidth(1);
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("background-color: rgba(255, 255, 255, 0.1);");
    m_pToolsLayout->addWidget(line,0);
}

