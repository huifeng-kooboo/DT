#include "images.h"
#include <QLayout>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include <QAbstractItemView>
#include <qabstractitemview.h>
#include <QDebug>

// 默认最多保存多少张图
#define MAX_IMAGE_SIZE 100

Images::Images(QObject*)
{
    /**
      * 设置Dll类型 后期优化的时候需要使用
     */
    setProperty("dllType",MSG_DLL_IMAGES);
    m_uiObject = nullptr;
    Q_INIT_RESOURCE(images);
}

void Images::loadUI()
{
    /**
    * @brief: 加载最下方图片框UI控件
    *
    */
    QWidget* pMainWidget = (QWidget*)(m_uiObject);
    m_pImageListWidget = new QListWidget();
    m_pImageListWidget->setObjectName("image_widget");
    m_pImageListWidget->setFixedSize(400,200);
    m_pImageListWidget->setGeometry(200,400,400,200);
    m_pImageListWidget->setIconSize(QSize(160,160));
    /*
     * 设置从左到右的排列
    */
    m_pImageListWidget->setViewMode(QListView::ListMode);
    m_pImageListWidget->setFlow(QListView::LeftToRight);
    m_pImageListWidget->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
    m_pImageListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QLayout* pLayout = pMainWidget->layout();
    pLayout->addWidget(m_pImageListWidget);
    testUiFunc();
}

QVariant Images::slotHandleMessage(const PluginMetaData &plt)
{
    return QVariant("");
}

void Images::slotEventFromPlugins(const PluginMetaData& plt)
{
    //sendSignal(plt);
    m_uiObject = plt.qObject;
}


void Images::saveImageToWidgetList(const QIcon &qIcon,const QString&objName)
{
    int nCount = m_pImageListWidget->count();
    if(nCount > MAX_IMAGE_SIZE)
    {
        qDebug()<< "按照时间顺序删除";
    }
    QListWidgetItem * pListWidgetItem = new QListWidgetItem();
    pListWidgetItem->setData(0,objName);
    pListWidgetItem->setIcon(qIcon);
    m_pImageListWidget->addItem(pListWidgetItem);
}

void Images::setImageWidgetIconSize(const int &width, const int &height)
{
    m_pImageListWidget->setIconSize(QSize(width,height));
}

void Images::testUiFunc()
{
    /*
     * 测试ListWidget功能
     */
    for(int i = 0; i < 10; i++)
    {
         m_pImageListWidget->addItem(new QListWidgetItem(QIcon(":/resources/test.png"),""));
    }
}
