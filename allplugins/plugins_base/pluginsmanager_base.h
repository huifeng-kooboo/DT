#ifndef PLUGINSMANAGER_BASE_H
#define PLUGINSMANAGER_BASE_H
#include <QObject>
#include <QPushButton>
#include <QApplication>
#include <QFile>
#include "../../global/define.h"


#define PRIVATE_METHOD private
#define PUBLIC_METHOD public

// 处理中文乱码使用
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

// 子插件通用的基类模块
class DTPluginBase: public QObject
{

    Q_OBJECT

public:
    // 所有插件均需要实现loadUI()方法，可以是空实现
    virtual void loadUI() = 0;

Q_SIGNALS:

    /**
      * @brief: 同步方法：直接获取返回值处理
     */
    QVariant signalSendMessage(const PluginMetaData&);

    /*
     * @brief: 同步信号
     */
    void sendSignalToPlugins(const PluginMetaData&);

    /**
      * 异步信号增加
     */
    void sendSignalToPluginsAsync(const PluginMetaData&);

PUBLIC_METHOD:

    /**
      * @brief: 同步发送信号
      */
    virtual void sendSignal(const PluginMetaData& plt)
    {
        emit sendSignalToPlugins(plt);
    }

    /**
      * @brief: 异步发送信号
      */
    virtual void sendSignalAsyn(const PluginMetaData& plt)
    {
        emit sendSignalToPluginsAsync(plt);
    }

private:
    // 加载样式表
    void loadStyleSheet(const QString& qsStyleFile)
    {
        QFile qss(qsStyleFile);
        qss.open(QFile::ReadOnly);
        // 需要去覆盖对应文件
        qApp->setStyleSheet(qApp->styleSheet() + qss.readAll());
        qss.close();
    }

public slots:


    /**
      * @brief: 处理回调事件
      * 处理事件当中的名称
      */
    virtual void slotEventFromPlugins(const PluginMetaData& plt) = 0;

    /**
      * @brief: 设置UI句柄
      * ex: 在loadUi信号中会进行设置绑定
      */
    virtual void slotSetUIHandle(QObject* uiObject)
    {
        if(uiObject != nullptr)
        {
            m_uiObject = uiObject;
            // 加载UI事件
            loadUI();
        }
    }

    /**
     * @brief: 同步消息处理
     * 返回值：返回同步结果
     */
    virtual QVariant slotHandleMessage(const PluginMetaData& plt) = 0;


    /**
      * @brief: 发送信号槽函数
      */
    virtual void slotSendSignal(const PluginMetaData& plt)
    {
        sendSignal(plt);
    }


public:

    /**
     * @brief: 主窗口句柄
     */
    QObject* m_uiObject;
};

#endif // PLUGINSMANAGER_BASE_H
