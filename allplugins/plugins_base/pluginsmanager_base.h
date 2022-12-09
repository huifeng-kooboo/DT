#ifndef PLUGINSMANAGER_BASE_H
#define PLUGINSMANAGER_BASE_H
#include <QObject>
#include <QPushButton>
#include "../../global/define.h"

// 处理中文乱码使用
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

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

    /*
     * 添加工具
    */
    void signalAddTitleBtn(QPushButton*);

     /*
     * 添加工具栏按钮信号
     */
    void signalAddToolBtn(QPushButton* ,bool, Qt::Alignment );

    /*
     * @brief: 添加TabWidget
     *
    */
    void signalAddTabWidget(QString ,QIcon, QWidget*,bool);

    /*
     * @brief: 状态栏增加控件
     * pWidget： 需要底部状态栏增加的控件句柄
     * strech: 默认0即可
    */
    void signalAddStatusBarControls(QWidget* pWidget,int strech); // 底部状态栏增加控件接口

    /*
     * @brief: 显示状态栏信息
     *
    */
    void signalShowStatusBarInfo(QString);

    /*
     * @brief: 设置主界面的Widget
    */
    void signalSetMainWidget(QWidget*);



public:

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

public slots:


    /**
      * @brief: 处理回调事件
      */
    virtual void slotEventFromPlugins(const PluginMetaData& plt) = 0;

    // 设置ui句柄
    virtual void slotSetUIHandle(QObject* uiObject)
    {
        if(uiObject != nullptr)
        {
            m_uiObject = uiObject;
            loadUI();
        }
    }

    /**
     * @brief: 同步消息处理
     * 返回值：返回同步结果
     */
    virtual QVariant slotHandleMessage(const PluginMetaData& plt) = 0;


    virtual void slotSendSignal(PluginMetaData plt)
    {
        sendSignal(plt);
    }


public:

    QObject* m_uiObject;
};

#endif // PLUGINSMANAGER_BASE_H
