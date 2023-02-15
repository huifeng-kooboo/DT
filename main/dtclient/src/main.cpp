#include "mainwindow.h"
#include "globaldefine.h"
#include "../../common/include/dtlog.h"
#include "../../common/include/dtregistry.h"
#include "dumper.h"
#ifdef Q_OS_WIN
#include <windows.h>
#endif

/**
 * [支持自定义扩展]
 * @brief: 解析命令行启动传参
 * @param: qsCmd: 传入参数
*/
void parseCmd(const QString& qsCmd)
{
    Logger->logMsg(QtMsgType::QtInfoMsg,QString("GetCmdInput: %1").arg(qsCmd),true);
    if(qsCmd.contains("debug"))
    {
        Logger->logMsg(QtMsgType::QtDebugMsg,QString("[调试]开启调试模式"));
        // 开启调试模式
#ifdef Q_OS_WIN
        AllocConsole();
        freopen("CONOUT$","w",stdout);
#endif
    }
}


/**
  * @brief: 获取屏幕分辨率比例
  *
*/
qreal getScreenPercent()
{
    // 获取屏幕放大比例....
    qreal displayPer = qApp->primaryScreen()->logicalDotsPerInch();
    Logger->logMsg(QtMsgType::QtDebugMsg,QString("WindowsDisplayPer: %1...").arg(displayPer));
    return displayPer;
}

int main(int argc, char *argv[])
{
    // dump文件生成
    SetUnhandledExceptionFilter(ExceptionFilter);

    // 注册需要通信的数据类型
    qRegisterMetaType<PluginMetaData>("PluginMetaData");

    // 设置UTF-8格式
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif

    // 设置程序的基本信息
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setApplicationName(APP_NAME);


    /**
     * 处理命令行输入信息
     */
    QString qsCmd="";
    for(int a = 0; a < argc; ++a)
    {
        qsCmd += QByteArray(argv[a], -1);
        if(a < argc-1)
            qsCmd += ";";
    }
    if(!qsCmd.isEmpty())
    {
        parseCmd(qsCmd);
    }

    /**
     * @brief: 初始化相关操作
    */
    QApplication app(argc, argv);

    // 日志类初始化
    if(Logger->createLogPath("",APP_NAME))
    {
        qInstallMessageHandler(DTLog::logMsg);
    }

    Logger->logFuncTime("BASIC_INIT");

    // 获取屏幕放大比例....
    getScreenPercent();

    // 资源初始化
    Q_INIT_RESOURCE(dtclient);

    Logger->logFuncTime("RESOURCE_INIT");

    // 启动主窗体
    MainWindow w;
    w.setWindowTitle(APP_NAME);

    // 默认最大化显示窗体
    w.showMaximized();

    Logger->logFuncTime("WINDOW_INIT");

    return app.exec();
}
