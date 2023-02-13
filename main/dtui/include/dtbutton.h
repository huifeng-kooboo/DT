#ifndef DTBUTTON_H
#define DTBUTTON_H

#include "dt_stylesheets.h"

enum E_BUTTON_TYPE{
   BUTTON_NORMAL,
   BUTTON_MINI,
   BUTTON_BIG
};

enum E_BUTTON_STATE{
    BUTTON_STATE_HOVER,
    BUTTON_STATE_PRESSED,
    BUTTON_STATE_DISABLE,
    BUTTON_STATE_NORMAL,
    BUTTON_STATE_CHECKED,
    BUTTON_STATE_UNCHECKED,
};

class DTButton: public QPushButton
{
    Q_OBJECT

public:

    DTButton(QWidget* pWidget = nullptr);

   /**
     * @brief: 设置按钮颜色
    */
   void setBtnStateColor(E_BUTTON_STATE state,const QString& qColor);

   /**
     * @brief: 设置按钮文字颜色
    */
   void setBtnTextStateColor(E_BUTTON_STATE state,const QString& qColor);

   /**
     * 设置按钮固定大小
    */
   void setBtnFixedSize(const QSize& qSize);


   /**
    * @brief: 设置按钮文字大小
   */
   void setBtnFontSize(int nPixel);

   /**
    * @brief: 设置Radius
   */
   void setBtnRadius(int nRadius);

   /**
     * @brief: 设置按钮字体
   */
   void setBtnFont(const QFont& qFont);

   /**
     * @brief: 设置Hover的窗体
   */
   void setHoverWidget(QWidget* pWidget)
   {
       m_pHoverWidget = pWidget;
   }

   /**
     * @brief: 设置Pressed的窗体
     */
   void setPressedWidget(QWidget* pWidget)
   {
      m_pPressedWidget = pWidget;
   }

   /**
     * @brief: 是否需要关闭按钮
   */
   void setCloseBtn(bool bClose)
   {
       m_bNeedClose = bClose;
   }
   bool isNeedClose()
   {
       return m_bNeedClose;
   }

   /**
    * @brief: 设置icon 多种状态
    */
   void setStateIcon(QIcon normalIcon, QIcon hoverIcon, QIcon pressedIcon)
   {
       m_normalIcon = normalIcon;
       m_hoverIcon = hoverIcon;
       m_pressedIcon = pressedIcon;
   }

signals:
   void signalCloseTab(QString tabName);

protected:
   bool event(QEvent *e) override;
   void paintEvent(QPaintEvent *) override;
   void mousePressEvent(QMouseEvent *e) override;
   void mouseReleaseEvent(QMouseEvent *e) override;
   void mouseMoveEvent(QMouseEvent *e) override;
   void focusInEvent(QFocusEvent *) override;
   void focusOutEvent(QFocusEvent *) override;
   void enterEvent(QEvent* event) override;
   void leaveEvent(QEvent*event) override;

private:
   QFont m_Font;
   int n_FontSize;
   bool m_bNeedClose = false;
   QImage m_image ;

   /**
     * @brief: 默认三种状态下的Icon
    */
   QIcon m_normalIcon;
   QIcon m_hoverIcon;
   QIcon m_pressedIcon;

   /**
     * @brief: hover时的显示窗体
    */
   QWidget* m_pHoverWidget = nullptr;

   /**
     * @brief: Pressed时候的窗体
    */
   QWidget* m_pPressedWidget = nullptr;
};

#endif // DTBUTTON_H
