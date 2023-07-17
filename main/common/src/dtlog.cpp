#include "dtlog.h"

// static variables
static DTLog *g_pLog = nullptr;
static QFile g_logFile;
static bool g_bLog = false;
static QString g_qsLogPath = "";

bool DTLog::isOpenLog = true;

DTLog::DTLog() {}

DTLog::~DTLog() { qDebug() << "~DTLog()"; }

DTLog *DTLog::getLog() {
    if (g_pLog == NULL) {
        g_pLog = new DTLog;
    }
    return g_pLog;
}

void DTLog::setLoggerState(bool isOpen)
{
    DTLog::isOpenLog = isOpen;
}

bool DTLog::createLogPath(const QString &qsSubPath, const QString &qsFileName) {
    QString qsDateTime = QDateTime::currentDateTime().toString("yyyyMMdd");
    g_qsLogPath = qApp->applicationDirPath();
    qDebug() << g_qsLogPath;
    if(qsSubPath == "")
    {
        g_qsLogPath.append("/Logs/");
    }
    else{
        g_qsLogPath.append("/"+qsSubPath);
    }
    QDir dir(g_qsLogPath);
    if (!dir.exists()) {
        if (!dir.mkpath(g_qsLogPath)) {
            qDebug() << "create file path fail:" << g_qsLogPath;
            return false;
        }
    } else {
        QStringList qlFilter("*.log");
        QStringList qlLogsList = dir.entryList(qlFilter);
        if (qlLogsList.size() >= MAX_LOGS_NUM) {
            QString qsRemoveLogFolder = dir.absolutePath();
            qsRemoveLogFolder.append("/").append(qlLogsList.at(0));
            if (!QFile::remove(qsRemoveLogFolder))
                qDebug() << "delete file err:" << qsRemoveLogFolder;
        }
    }
    g_qsLogPath =
            g_qsLogPath.append(DTLOG_PATH_FILENAME).arg(qsFileName).arg(qsDateTime);
    g_bLog = true;
    return true;
}

void DTLog::logMsg(QtMsgType type, const QString &qsMsg, bool isNeedDebug)
{
    if (!DTLog::isOpenLog)
    {
        return;
    }
    if(isNeedDebug)
    {
        qDebug() << "[LOG_INFO]: " << qsMsg ;
    }
    static QMessageLogContext qlc;
    logMsg(type,qlc,qsMsg);
}

void DTLog::logFuncTime(const QString &functionName)
{
    if (!DTLog::isOpenLog)
    {
        return;
    }
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString qsCurrentDate =current_date_time.toString("yyyy.MM.dd.hh:mm:ss.zzz");
    QString qsMsg = QString("[LOG_PERFORMACE]%1 FINISHED AT TIME %2.").arg(functionName).arg(qsCurrentDate);
    qDebug() << qsMsg;
    static QMessageLogContext qlc;
    logMsg(QtMsgType::QtInfoMsg,qlc,qsMsg);
}

void DTLog::logMsg(QtMsgType type,const QMessageLogContext &context,const QString &qsMsg) {
    if (!DTLog::isOpenLog)
    {
        return;
    }
    Q_UNUSED(context);
    if (g_bLog == false)
    {
        return;
    }
    static QMutex mutex;
    mutex.lock();
    QString text;
    switch (type) {
    case QtDebugMsg:
        text = QString("[DEBUG]");
        break;
    case QtInfoMsg:
        text = QString("[INFO]");
        break;

    case QtWarningMsg:
        text = QString("[WARNING]");
        break;

    case QtCriticalMsg:
        text = QString("[CRITICAL]");
        break;

    case QtFatalMsg:
        text = QString("[FATAL]");
    default:
        break;
    }

    int index = qsMsg.lastIndexOf('\\');
    QString msgNew = qsMsg.right(qsMsg.length() - index - 1);
    static bool bfirstOpen = true;
    QIODevice::OpenMode openMode = QIODevice::ReadWrite | QIODevice::Text;
    {
        g_logFile.setFileName(g_qsLogPath);
        openMode |= QIODevice::Append;
    }
    bool bOpenSuccess = g_logFile.open(openMode);
    if (bOpenSuccess) {
        bfirstOpen = false;
        QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QString message = QString("%1 %2 %3").arg(current_date_time).arg(text).arg(msgNew);
        QTextStream txtOutput(&g_logFile);
        txtOutput << message << "\r\n";
        g_logFile.flush();
        g_logFile.close();
    }
    mutex.unlock();
}

void DTLog::functionStart(const QString &qsFunctionName)
{
    //todo
    Q_UNUSED(qsFunctionName);
}



void DTLog::functionEnd(const QString &qsFunctionName)
{
    //todo
    Q_UNUSED(qsFunctionName);
}
