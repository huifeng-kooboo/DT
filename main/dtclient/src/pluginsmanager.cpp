#include "pluginsmanager.h"
#include <QFile>
#include <QLibrary>
#include <QPluginLoader>
#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include "globaldefine.h"
#include "../../common/include/dtjson.h"
#include "../../common/include/dtlog.h"

// 处理中文乱码使用
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif


#define PLUGINS  "plugins/"

bool DT_PluginsManager::loadPlugin(const QString &dllPath, bool bFreeWhenFailed)
{
    if(!QFile::exists(dllPath))
        return false;
    QPluginLoader qLibrary(dllPath);
    if(qLibrary.load())
    {
        Logger->logMsg(QtMsgType::QtInfoMsg,tr("加载插件成功，插件地址：%1").arg(dllPath));
        return true;
    }
    QString qsError  = qLibrary.errorString();
    if(bFreeWhenFailed)
        qLibrary.unload();

    Logger->logMsg(QtMsgType::QtFatalMsg,tr("%1加载失败,错误信息为:%2").arg(dllPath).arg(qsError));
    return false;
}

void DT_PluginsManager::loadPlugins()
{
    bool bLoaded = false;
    for(int i = 0; i < m_vecPluginInfo.size(); i++)
    {
        bLoaded = loadPlugin(m_vecPluginInfo.at(i).qsPluginsName,true);
        if(bLoaded == true)
        {
            m_vecLoadedPluginInfo.append(m_vecPluginInfo.at(i));
        }
        else{
            m_vecFailedPluginInfo.append(m_vecPluginInfo.at(i));
        }
    }
}

void DT_PluginsManager::freePlugin(const QString &dllPath)
{
    if(QFile::exists(dllPath))
    {
        QPluginLoader qlLibrary(dllPath);
        qlLibrary.unload();
    }
    return ;
}

void DT_PluginsManager::freePlugins()
{
    for(auto dllPath: m_vecLoadedPluginInfo)
    {
        if(QFile::exists(dllPath.qsPluginsName))
        {
            QPluginLoader loader(dllPath.qsPluginsName);
            if(loader.isLoaded() || loader.load())
            {
                // 双向绑定
                QObject::disconnect(loader.instance(),SIGNAL(sendSignalToPlugins(PluginMetaData)),m_parent,SLOT(slotEventFromPlugins(PluginMetaData)));
                QObject::disconnect(m_parent,SIGNAL(sendSignalToPlugins(PluginMetaData)),loader.instance(),SLOT(slotEventFromPlugins(PluginMetaData)));
                // 绑定更新ui事件
                QObject::disconnect(this,SIGNAL(sendSignalUI(QObject*)),loader.instance(),SLOT(slotSetUIHandle(QObject*)));
                // 标题栏工具图标绑定
                QObject::disconnect(loader.instance(),SIGNAL(signalAddTitleBtn(QPushButton*)),m_parent,SLOT(slotPluginAddTitleBtn(QPushButton*)));
                // 绑定添加工具栏图标控件
                QObject::disconnect(loader.instance(),SIGNAL(signalAddToolBtn(QPushButton*,bool ,Qt::Alignment)),m_parent,SLOT(slotPluginAddToolBtn(QPushButton*,bool ,Qt::Alignment)));
                // 添加TabWidget
                QObject::disconnect(loader.instance(),SIGNAL(signalAddTabWidget(QString ,QIcon, QWidget*,bool)),m_parent,SLOT(slotPluginAddTabWidget(QString ,QIcon, QWidget*,bool)));
                // 添加状态栏控件
                QObject::disconnect(loader.instance(),SIGNAL(signalAddStatusBarControls(QWidget*,int)),m_parent,SLOT(slotPluginAddStatusBarControls(QWidget*,int)));
                // 绑定显示状态栏信息事件
                QObject::disconnect(loader.instance(),SIGNAL(signalShowStatusBarInfo(QString)),m_parent,SLOT(slotPluginShowStatusBarInfo(QString)));

                // 解除绑定

            }

            bool bUnload = loader.unload();
            if(!bUnload)
            {
                qDebug() << "unload";
            }
        }
    }
    return;
}

DT_PluginsManager::DT_PluginsManager(QObject *parent)
{
    QJsonDocument qsDoc;
    bool isRead =  JSON.readJsonByFile("plugins/plugins.json",qsDoc);
    if(isRead)
    {
        QJsonObject qObj = qsDoc.object();
        QJsonValue qsValue = qObj.value("plugins");
        QJsonArray qjsArray = qsValue.toArray();
        for(auto qJson:qjsArray)
        {
            PluginsInfo pluginInfo;
            QJsonValue qjsValue =qJson.toObject().value("plugins_name");
            QString qsPluginsVersion = qJson.toObject().value("plugins_version").toString();
            QString qsPluginsDesc = qJson.toObject().value("plugins_desc").toString();
            // 之后使用
            QString qsPluginsState = qJson.toObject().value("plugins_state").toString();
            pluginInfo.qsPluginsName = QString(PLUGINS).append(qjsValue.toString());
            pluginInfo.qsPluginsDesc = qsPluginsDesc;
            pluginInfo.qsPluginsVersion = qsPluginsVersion;
            pluginInfo.ePluginState = qsPluginsState.toInt() == 0 ? E_PLUGIN_STATE::PLUGIN_DIRECT : E_PLUGIN_STATE::PLUGIN_DYNAMIC;
            if(pluginInfo.ePluginState == E_PLUGIN_STATE::PLUGIN_DIRECT)
            {
                m_vecPluginInfo.append(pluginInfo);
            }
            else{
                // 需要动态加载的dll
                m_vecDynamicPluginInfo.append(pluginInfo);
            }
        }
        m_parent = parent;
    }

}

DT_PluginsManager::~DT_PluginsManager()
{
    if(m_parent)
    {
        m_parent = nullptr;
        delete  m_parent;
    }
}

void DT_PluginsManager::registerEventCallBacks()
{
    for(auto pluginPath: m_vecLoadedPluginInfo)
    {
        if(QFile::exists(pluginPath.qsPluginsName))
        {
            QPluginLoader loader(pluginPath.qsPluginsName);
            if(loader.load() || loader.isLoaded())
            {
                m_vecLoadSuccessObjects.append(loader.instance());

                /**
                  * 同步方法信号槽绑定
                 */
                QObject::connect(loader.instance(),SIGNAL(sendSignalToPlugins(PluginMetaData)),m_parent,SLOT(slotEventFromPlugins(PluginMetaData)));
                QObject::connect(m_parent,SIGNAL(sendSignalToPlugins(PluginMetaData)),loader.instance(),SLOT(slotEventFromPlugins(PluginMetaData)));

                /**
                  * 异步方法信号槽绑定
                 */
                QObject::connect(loader.instance(),SIGNAL(sendSignalToPluginsAsync(PluginMetaData)),m_parent,SLOT(slotEventFromPluginsAsync(PluginMetaData)),Qt::ConnectionType::QueuedConnection);
                QObject::connect(m_parent,SIGNAL(sendSignalToPluginsAsync(PluginMetaData)),loader.instance(),SLOT(slotEventFromPlugins(PluginMetaData)),Qt::ConnectionType::QueuedConnection);

                /**
                  * @brief: 在同个线程中的同步方法
                  */
                QObject::connect(loader.instance(),SIGNAL(signalSendMessage(const PluginMetaData&)),m_parent,SLOT(slotSendMessage(const PluginMetaData&)),Qt::DirectConnection);


                // 绑定更新ui事件
                QObject::connect(this,SIGNAL(sendSignalUI(QObject*)),loader.instance(),SLOT(slotSetUIHandle(QObject*)));
                // 标题栏工具图标绑定
                QObject::connect(loader.instance(),SIGNAL(signalAddTitleBtn(QPushButton*)),m_parent,SLOT(slotPluginAddTitleBtn(QPushButton*)));
                // 绑定添加工具栏图标控件
                QObject::connect(loader.instance(),SIGNAL(signalAddToolBtn(QPushButton*,bool ,Qt::Alignment)),m_parent,SLOT(slotPluginAddToolBtn(QPushButton*,bool ,Qt::Alignment)));
                // 添加TabWidget
                QObject::connect(loader.instance(),SIGNAL(signalAddTabWidget(QString ,QIcon, QWidget*,bool)),m_parent,SLOT(slotPluginAddTabWidget(QString ,QIcon, QWidget*,bool)));
                // 添加状态栏控件
                QObject::connect(loader.instance(),SIGNAL(signalAddStatusBarControls(QWidget*,int)),m_parent,SLOT(slotPluginAddStatusBarControls(QWidget*,int)));
                // 绑定显示状态栏信息事件
                QObject::connect(loader.instance(),SIGNAL(signalShowStatusBarInfo(QString)),m_parent,SLOT(slotPluginShowStatusBarInfo(QString)));
                // 绑定设置当前Widget
                QObject::connect(loader.instance(),SIGNAL(signalSetMainWidget(QWidget*)),m_parent,SLOT(slotSetMainWidget(QWidget*)));
            }
        }
    }
}

void DT_PluginsManager::initUI(QObject* qoObject)
{
    emit sendSignalUI(qoObject);
}
