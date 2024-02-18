#ifndef DTGROUPBOX_H
#define DTGROUPBOX_H
#include <QLabel>
#include <QVBoxLayout>

class DTGroupBox: public QWidget
{
    Q_OBJECT
public:
    explicit DTGroupBox(QWidget* parent = nullptr);
    ~DTGroupBox();

    void setTitle(QString& qsTitle);
    void setContentWidget(QWidget* contentWidget);

private:
    QWidget * m_pParent;  // 父窗体
    QPushButton * m_pCloseBtn; // 关闭按钮
    QLabel* m_pTitle; // 标题
    QVBoxLayout * pVBoxLayout;
};

#endif // DTGROUPBOX_H

