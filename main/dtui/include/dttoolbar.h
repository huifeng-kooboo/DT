#ifndef DTTOOLBAR_H
#define DTTOOLBAR_H
#include<QHBoxLayout>
#include <QComboBox>
#include "dtbutton.h"

// 工具栏控件封装
class DTToolBar: public QWidget
{
    Q_OBJECT
public:
    explicit DTToolBar(QWidget* parent = nullptr);
    ~DTToolBar();

public:

    /*
     * @brief: 添加工具
     * qsToolName: 工具名称
     * qIcon: 工具图标
     * btn: 工具按钮
     * align: 图标放置位置，默认左侧
     */
    void addTool(const QString& qsToolName, QIcon qIcon, QPushButton* btn, Qt::Alignment align = Qt::AlignLeft);

    /*
     * @brief:设置背景颜色
     * qc: 需要设置的背景颜色
    */
    void setBackgroundColor(const QColor& qc);

    /**
     * @brief: 添加分割线
     */
    void addSplitLine();


private slots:
    void slotActivated(const QString& qsActivated);

private:
    QHBoxLayout* m_pBtnsLayout;
    QHBoxLayout* m_pToolsLayout;
    QVector<QPushButton*> m_vecBtns;
};


#endif // DTTOOLBAR_H
