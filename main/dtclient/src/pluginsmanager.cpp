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
    Logger->logMsg(QtMsgType::QtInfoMsg,"....FreePluginsFirst...");
    for(auto dllPath: m_vecLoadedPluginInfo)
    {
        if(QFile::exists(dllPath.qsPluginsName))
        {
            QPluginLoader loader(dllPath.qsPluginsName);
            if(loader.isLoaded())
            {
                Logger->logMsg(QtMsgType::QtInfoMsg,QString("....FreePlugins:%1...").arg(dllPath.qsPluginsName));
                QObject::disconnect(loader.instance(),SIGNAL(sendSignalToPlugins(const PluginMetaData&)),m_parent,SLOT(slotEventFromPlugins(const PluginMetaData&)));
                QObject::disconnect(m_parent,SIGNAL(sendSignalToPlugins(const PluginMetaData&)),loader.instance(),SLOT(slotEventFromPlugins(const PluginMetaData&)));

                QObject::disconnect(loader.instance(),SIGNAL(sendSignalToPluginsAsync(const PluginMetaData&)),m_parent,SLOT(slotEventFromPluginsAsync(const PluginMetaData&)));
                QObject::disconnect(m_parent,SIGNAL(sendSignalToPluginsAsync(const PluginMetaData&)),loader.instance(),SLOT(slotEventFromPlugins(const PluginMetaData&)));

                QObject::disconnect(loader.instance(),SIGNAL(signalSendMessage(PluginMetaData)),m_parent,SLOT(slotSendMessage(PluginMetaData)));
                // 解除绑定更新ui事件
                QObject::disconnect(this,SIGNAL(sendSignalUI(QObject*)),loader.instance(),SLOT(slotSetUIHandle(QObject*)));

            }

            bool bUnload = loader.unload();
            if(!bUnload)
            {
                Logger->logMsg(QtMsgType::QtInfoMsg,QString("....ThePlugin:%1 Is Error To Unload...").arg(dllPath.qsPluginsName));
                Logger->logMsg(QtMsgType::QtFatalMsg,QString("ErrorReason:%1").arg(loader.errorString()));
            }
        }
    }

     Logger->logMsg(QtMsgType::QtInfoMsg,"....FreePluginsEnd...");
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
            // ToDo: 完善对应的业务
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
                if (loader.instance()== nullptr)
                {
                    Logger->logMsg(QtMsgType::QtCriticalMsg, "当前实例为空");
                    return ;
                }
                m_vecLoadSuccessObjects.append(loader.instance());

                /**
                  * 同步方法信号槽绑定
                 */
                QObject::connect(loader.instance(),SIGNAL(sendSignalToPlugins(const PluginMetaData&)),m_parent,SLOT(slotEventFromPlugins(const PluginMetaData&)));
                QObject::connect(m_parent,SIGNAL(sendSignalToPlugins(const PluginMetaData&)),loader.instance(),SLOT(slotEventFromPlugins(const PluginMetaData&)));

                /**
                  * 异步方法信号槽绑定
                 */
                QObject::connect(loader.instance(),SIGNAL(sendSignalToPluginsAsync(const PluginMetaData&)),m_parent,SLOT(slotEventFromPluginsAsync(const PluginMetaData&)),Qt::ConnectionType::QueuedConnection);
                QObject::connect(m_parent,SIGNAL(sendSignalToPluginsAsync(const PluginMetaData&)),loader.instance(),SLOT(slotEventFromPlugins(const PluginMetaData&)),Qt::ConnectionType::QueuedConnection);

                /**
                  * @brief: 在同个线程中的同步方法
                  */
                QObject::connect(loader.instance(),SIGNAL(signalSendMessage(const PluginMetaData&)),m_parent,SLOT(slotSendMessage(const PluginMetaData&)),Qt::DirectConnection);


                /**
                 * @brief: 绑定更新UI事件
                 */
                QObject::connect(this,SIGNAL(sendSignalUI(QObject*)),loader.instance(),SLOT(slotSetUIHandle(QObject*)));
            }
            else {
                Logger->logMsg(QtMsgType::QtWarningMsg, "Dll加载失败......");
            }
        }
    }
}

void DT_PluginsManager::loadPluginUi(QObject* qoObject)
{
    emit sendSignalUI(qoObject);
}
