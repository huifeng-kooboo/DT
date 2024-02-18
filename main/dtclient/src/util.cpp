#include "../include/util.h"
#ifdef Q_OS_WIN
#include <windows.h>
#endif

void Util::processCmd(int argc, char *argv[])
{
    // 处理命令行参数
    QString qsCmd="";
    for(int a = 0; a < argc; ++a)
    {
        qsCmd += QByteArray(argv[a], -1);
        if(a < argc-1)
            qsCmd += ";";
    }

    if(qsCmd.contains("debug"))
    {
        // 开启调试模式
#ifdef Q_OS_WIN
        AllocConsole();
        freopen("CONOUT$","w",stdout);
#endif
    }
}

void Util::setDefaultCodec(QString qsFormat)
{
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
    QTextCodec *codec = QTextCodec::codecForName(qsFormat.toStdString().c_str());
    QTextCodec::setCodecForLocale(codec);
#endif
}
