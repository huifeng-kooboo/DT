#ifndef ACCOUNT_WIDGET_H
#define ACCOUNT_WIDGET_H

class AccountWidget: public QWidget{
public:
    AccountWidget(QWidget* pWidget);
    ~AccountWidget();


private:
    void init();


private:
    QVBoxLayout* m_pMainLayout;

    QHBoxLayout* m_pLoginLayout;
    QHBoxLayout* m_pInfoLayout;


    // 相关控件按钮
    QLabel* m_pLogoLabel;
    QPushButton* m_pLoginButton;
    QPushButton* m_pInfoButton;
};

#endif // ACCOUNT_WIDGET_H
