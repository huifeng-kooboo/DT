#ifndef DTFRAMELESSWIDGET_H
#define DTFRAMELESSWIDGET_H

/*
 * 无边框的窗体基类
*/
class DTFrameLessWidget: public QWidget
{
public:
    DTFrameLessWidget(QWidget* pParent = nullptr);
    ~DTFrameLessWidget();

private:
    QWidget* m_pParent;
};

#endif // DTFRAMELESSWIDGET_H
