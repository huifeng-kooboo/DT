#include <QApplication>
#include <QSettings>
#include <QTextCodec>
#include <QScreen>
#include <QHostInfo>
#include "mainwindow.h"
#include "globaldefine.h"
#include "../../common/include/dtlog.h"
#include "../../common/include/dtregistry.h"
#include "dumper.h"
#ifdef Q_OS_WIN
#include <windows.h>
#endif

/**
 * @brief: 解析命令行启动传参
 * @param: qsCmd: 传入参数
*/
void parseCmd(const QString& qsCmd)
{
    //ToDo
    Logger->logMsg(QtMsgType::QtInfoMsg,QString("GetCmdInput: %1").arg(qsCmd));
    if(qsCmd.contains("debug"))
    {
        // 开启调试模式
#ifdef Q_OS_WIN
        AllocConsole();
        freopen("CONOUT$","w",stdout);
#endif
    }
}


int main(int argc, char *argv[])
{

    SetUnhandledExceptionFilter(ExceptionFilter);

     qRegisterMetaType<PluginMetaData>("PluginMetaData");
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

    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setApplicationName(APP_NAME);

#ifdef LOCAL_TEST
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.setValue("ip","192.168.0.216:20020");
#endif
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

    qreal displayPer = qApp->primaryScreen()->logicalDotsPerInch();
    Logger->logMsg(QtMsgType::QtInfoMsg,QString("...Init Window... DisplayPer: %1").arg(displayPer));
    Q_INIT_RESOURCE(dtclient);

    // 启动主窗体
    MainWindow w;
    w.showMaximized();
    Logger->logMsg(QtMsgType::QtInfoMsg,"App Exit");
    return app.exec();
}
