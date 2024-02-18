
#ifndef DTBUTTON_H
#define DTBUTTON_H

#include "dt_stylesheets.h"

enum E_BUTTON_TYPE{
   BUTTON_NORMAL, // 正常大小
   BUTTON_MINI,
   BUTTON_BIG,
   BUTTON_CIRCLE, // 原型
   BUTTON_TRIANGLE, // 椭圆
};

enum E_BUTTON_STATE{
    BUTTON_STATE_HOVER,
    BUTTON_STATE_PRESSED,
    BUTTON_STATE_DISABLE,
    BUTTON_STATE_NORMAL,
    BUTTON_STATE_CHECKED,
    BUTTON_STATE_UNCHECKED,
};

enum E_BUTTON_SHAPE {
    DEFAULT,
    CIRCLE,
    TRIANGLE
};

class DTButton: public QPushButton
{
    Q_OBJECT

public:

    DTButton(QWidget* pWidget = nullptr);


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

};

#endif // DTBUTTON_H
