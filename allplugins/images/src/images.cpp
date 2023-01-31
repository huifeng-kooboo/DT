#include "images.h"


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
    * @brief: 添加测试按钮控件增加
    *
    */
    if (m_uiObject != nullptr)
    {
        QWidget* pMainWidget = dynamic_cast<QWidget*>(m_uiObject);

        m_pTestBtn = QSharedPointer<DTButton>(new DTButton(pMainWidget),&QObject::deleteLater);
        m_pTestBtn->setText("test_ok");
        m_pTestBtn->setStyleSheet("background-color: rgb(26, 26, 26); color:rgb(250, 250, 250);");
        m_pTestBtn->setGeometry(100,200,100,200);
        m_pTestBtn->show();
    }

}

QVariant Images::slotHandleMessage(const PluginMetaData &plt)
{
    // 同步消息处理
    return QVariant("");
}

void Images::slotEventFromPlugins(const PluginMetaData& plt)
{
    // 异步事件

    m_uiObject = plt.qObject;
    switch (plt.enumUiMsg) {
    case E_UI_MSG_TYPE::MSG_UI_NONE:
        break;
    default:
        break;
    }
}
