#include "widgets/sidebar_widget.h"

SideBarWidget::SideBarWidget(QWidget* pParent):QWidget(pParent)
{
    init();
}

void SideBarWidget::init()
{
    initStyle();
    initData();
}

void SideBarWidget::initStyle()
{
    this->setStyleSheet("QWidget{ background-color: rgb(27, 27, 28); color: rgb(212, 212, 212); }");
    m_pVBoxLayout = new  QVBoxLayout();
    this->setLayout(m_pVBoxLayout);
}

void SideBarWidget::initData()
{

}

SideBarWidget::~SideBarWidget()
{

}
