#include "mainwindow.h"
#include "globaldefine.h"
#include "../../common/include/dtlog.h"
#include "../../common/include/dtregistry.h"
#include "../include/util.h"
#include "win/dumper.h"

int main(int argc, char *argv[])
{

#ifdef Q_OS_WIN
#ifdef DUMP_GENERATE
    SetUnhandledExceptionFilter(ExceptionFilter);
#endif
#endif
    // 注册需要通信的数据类型
    qRegisterMetaType<PluginMetaData>("PluginMetaData");

    // 设置默认编码格式
    Util::setDefaultCodec();

    // 处理命令行
    Util::processCmd(argc,argv);

    // 设置程序的基本信息
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setApplicationName(APP_NAME);

    /**
     * @brief: 初始化相关操作
    */
    QApplication app(argc, argv);

    // 日志初始化
    if(Logger->createLogPath("",APP_NAME))
    {
        qInstallMessageHandler(DTLog::logMsg);
    }

    // 资源初始化
    Q_INIT_RESOURCE(dtclient);

    // 启动主窗体
    MainWindow w;
    // w.setWindowTitle(APP_NAME);
    return app.exec();
}
