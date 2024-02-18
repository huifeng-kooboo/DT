#ifndef DTTOOLSET_H
#define DTTOOLSET_H
#include "../include/dtbutton.h"

///
/// \brief 工具集的类
///
class DTToolSet: public QWidget
{
        Q_OBJECT
public:
    DTToolSet(QWidget* pWidget);
    ~DTToolSet();

    ///
    /// \brief addToolButton
    /// \param pButton
    ///
    void addToolButton(DTButton* pButton);

    ///
    /// \brief getAllButtons 获取所有按钮的列表
    /// \return
    ///
    QVector<DTButton*> getAllButtons();

private:
    QWidget* m_pParentWidget; // 父类窗体
    QVector<DTButton*> m_vecButtons; // 按钮集合
};

#endif // DTTOOLSET_H
