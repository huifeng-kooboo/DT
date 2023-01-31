#include "widgets/account_widget.h"

AccountWidget::AccountWidget(QWidget* pWidget): QWidget(pWidget)
{
    m_pMainLayout = new QVBoxLayout();

    m_pLoginLayout = new QHBoxLayout();
    m_pInfoLayout = new QHBoxLayout();
    this->setLayout(m_pMainLayout);

    m_pLogoLabel = new QLabel();
    m_pLoginButton = new QPushButton();
    m_pInfoButton = new QPushButton();
    init();
}

AccountWidget::~AccountWidget()
{

}

void AccountWidget::init()
{
    this->setStyleSheet("QWidget { background-color:rgb(36, 36, 37); color:rgb(229, 229, 229); border-radius:8px; }");

    m_pMainLayout->addLayout(m_pLoginLayout);
    m_pMainLayout->addLayout(m_pInfoLayout);


   // m_pLogoLabel->setPixmap();

}
