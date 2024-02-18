#ifndef GLOBAL_DEFINE_BASE_H
#define GLOBAL_DEFINE_BASE_H

#include <QJsonObject>
#include <QObject>
#include <QVariant>

// DLL名称类型 [可扩展]
enum E_MSG_TYPE {
    MSG_NONE,      // None
    MSG_DLL_MAIN,  // 主程序
    MSG_DLL_SERVICE, // 服务dll，跟底层SDK或者HTTP请求交互的模块
    MSG_DLL_IMAGES, // IMAGES使用 DLL
};

// UI业务相关类型枚举 [可扩展]
// 事件定义规范: MSG_UI_dll名称_事件名称
// @brief: 主程序打开事件，则为MSG_UI_MAIN_OPEN : 统一的规范 方便管理
enum E_UI_MSG_TYPE {
    MSG_UI_NONE,  // None
    MSG_UI_MAIN_OPEN, // 打开事件
    MSG_UI_MAIN_CLOSE, // 关闭程序

    //Image
    MSG_UI_IMAGE_HOT_PINK = 1000, // HOT
};


/**
  * @brief: 通信结构体 【通用】
  *
*/
struct PluginMetaData {
    bool bNeedAll;                           // 是否需要所有插件进行处理: true: all 处理【预留】
    QString qsSenderName;                    // 发送事件的发送者名称, 可为空【预留】
    QString qsReceiveName;                   // 需要处理的dll的名称，可为空【预留】
    E_MSG_TYPE enumMsg;                       // DLL类型【预留】
    E_UI_MSG_TYPE enumUiMsg;                 // ui/业务消息类型【预留】
    QVariant qvCustomData ;                    // 自定义数据等【预留】
    QObject *qObject = nullptr;             // 传递窗体句柄 绘制界面
    QJsonObject qjExtraInfo = QJsonObject(); // 可扩展字段预留【预留】
    QMap<QString,QVariant> qmapValue;     // 可扩展字段: 针对于结构体等类型 QJsonObject不支持增加【预留】
};
Q_DECLARE_METATYPE(PluginMetaData);  //消息

#endif
