#ifndef PLAYSLIDER_H
#define PLAYSLIDER_H

/**
  * 进度条窗体
*/
class PlaySlider: public QWidget{
    Q_OBJECT
public:

private:
    void initControls();

private:
    QSlider * m_pSlider; // 滑动条
    QLineEdit* m_pLineEdit; // 编辑框
    QLabel* m_pProgressLabel; // 进度页面
};

#endif // PLAYSLIDER_H
