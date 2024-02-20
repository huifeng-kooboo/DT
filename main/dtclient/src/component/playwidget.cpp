#include "component/playwidget.h"

PlayWidget::PlayWidget(QWidget* pWidget)
{
    m_pParentWidget = pWidget;
    m_pMainLayout = new QHBoxLayout();
    setLayout(m_pMainLayout);
}

PlayWidget::~PlayWidget(){
    qDebug() << "Play Widget Delete..." << endl;
}

void PlayWidget::addPlayButton(QWidget *playBtn)
{
    m_pMainLayout->addWidget(playBtn);
}
