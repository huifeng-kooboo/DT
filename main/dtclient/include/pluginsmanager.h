#ifndef PLUGINSMANAGER_H
#define PLUGINSMANAGER_H

#define PluginManager DT_PluginsManager::GetInstance()

// 插件状态【分两种，一种是动态加载:即启动后不立即加载的，一种是直接加载】
enum E_PLUGIN_STATE {
  PLUGIN_DIRECT = 0, // 直接加载
  PLUGIN_DYNAMIC,    //动态加载
};

// 定义插件基本信息
struct PluginsInfo {
  QString qsPluginsName;       // 插件名称
  QString qsPluginsVersion;    //插件版本
  QString qsPluginsDesc;       //插件描述
  E_PLUGIN_STATE ePluginState; //插件状态
};


/**
 * @brief: 插件管理器
 * 主要是用来管理已经加载的插件，以及在程序运行结束后释放插件，这个就是组件化代码的核心
 * 通过读取 plugins/plugins.json 的文件列表 进行加载插件
*/
class DT_PluginsManager : public QObject {
  Q_OBJECT
  typedef QVector<PluginsInfo> VEC_PLUGININFO;

public:
  DT_PluginsManager(QObject *parent = nullptr);
  static DT_PluginsManager &GetInstance() {
    static DT_PluginsManager instance;
    return instance;
  }

  ~DT_PluginsManager();

  /**
    * @brief: 加载插件
    */
  static bool loadPlugin(const QString &dllPath, bool bFreeWhenFailed);

  /**
   * @brief: 释放指定的插件
   */
  static void freePlugin(const QString &dllPath);

  /**
   * @brief: 加载所有插件
   */
  void loadPlugins();

  /**
    * @brief: 释放插件列表
    */
  void freePlugins();

  /**
    * @brief: 注册插件的信号和槽
   */
  void registerEventCallBacks();

  /**
    * @brief: 加载插件内部的UI方法
   */
  void loadPluginUi(QObject *);

  /**
    * @brief: 获取以及加载成功的插件列表
    */
  const QVector<QObject*>& getLoadedObject()
  {
      return m_vecLoadSuccessObjects;
  }

signals:
  void sendSignalUI(QObject *);

private:
  VEC_PLUGININFO m_vecLoadedPluginInfo;  // 已经加载成功的dll列表
  VEC_PLUGININFO m_vecFailedPluginInfo;  // 加载失败的dll列表
  VEC_PLUGININFO m_vecPluginInfo;        // 需要加载的dll列表
  VEC_PLUGININFO m_vecDynamicPluginInfo; // 动态加载的dll
  QObject *m_parent;                     // 窗口句柄
  QVector<QObject*> m_vecLoadSuccessObjects;  // 获取已经加载的列表
};

#endif // PLUGINSMANAGER_H
