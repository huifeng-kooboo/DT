#include "dttoolset.h"

DTToolSet::DTToolSet(QWidget*pWidget)
{
    m_pParentWidget = pWidget;
}

void DTToolSet::addToolButton(DTButton *pButton)
{
    m_vecButtons.append(pButton);
}

QVector<DTButton*> DTToolSet::getAllButtons()
{
    return m_vecButtons;
}
