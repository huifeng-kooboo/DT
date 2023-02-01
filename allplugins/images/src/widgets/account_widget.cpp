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

    m_pLogoLabel->setStyleSheet("QLabel{background-color: rgb(53, 53, 54); color: rgb(128, 128, 128);}");
    m_pInfoButton->setStyleSheet("QPushButton{background-color: rgb(53, 53, 54); color: rgb(128, 128, 128); font:12px;}");

    m_pInfoButton->setText("开通会员得 100GB 云空间");
    m_pInfoButton->setFlat(true);

    m_pLoginButton->setText("点击登录账户");
    m_pLoginButton->setFlat(true);
   // m_pLogoLabel->setPixmap();

}
