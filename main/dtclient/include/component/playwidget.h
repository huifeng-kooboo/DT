#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H
#include <QHBoxLayout>

/**
  * @brief: 播放器组件
*/
class PlayWidget: public QWidget {
    Q_OBJECT
public:
    explicit PlayWidget(QWidget* parent = nullptr);
    ~PlayWidget();

    void addPlayButton(QWidget* playBtn);

private:
    QWidget * m_pParentWidget;
    QHBoxLayout * m_pMainLayout;
};

#endif // PLAYWIDGET_H
