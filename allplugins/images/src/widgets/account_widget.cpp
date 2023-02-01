#include "widgets/account_widget.h"

#pragma execution_character_set("utf-8")

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
    this->setStyleSheet("QWidget { background-color:rgb(36, 36, 37); color:rgb(229, 229, 229);  font-family:'Microsoft YaHei'; border-radius:8px; }");

    m_pMainLayout->addLayout(m_pLoginLayout);
    m_pMainLayout->addLayout(m_pInfoLayout);

    m_pLogoLabel->setStyleSheet("QLabel{background-color: rgb(53, 53, 54); color: rgb(128, 128, 128); font: 12px;}");
    m_pInfoButton->setStyleSheet("QPushButton{background-color: rgb(53, 53, 54); color: rgb(128, 128, 128); font:12px; font-weight:bold; border-radius: 5px;}");
    m_pLoginButton->setStyleSheet("QPushButton{ font: 12px; font-weight:bold;}");
    m_pInfoButton->setFixedHeight(30);

    m_pInfoButton->setText("开通会员得 100GB 云空间");
    m_pInfoButton->setFlat(true);

    m_pLogoLabel->setPixmap(QPixmap(":/resources/login.png"));
    m_pLoginButton->setText("点击登录账户");
    m_pLoginButton->setIcon(QIcon(":/resources/login.png"));
    m_pLoginButton->setFlat(true);

    //m_pLoginLayout->addWidget(m_pLogoLabel);
    m_pLoginLayout->addWidget(m_pLoginButton);
    m_pInfoLayout->addWidget(m_pInfoButton);
   // m_pLogoLabel->setPixmap();

}
