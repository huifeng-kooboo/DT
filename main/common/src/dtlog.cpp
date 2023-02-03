#include "dtlog.h"

// static variables
static DTLog *g_pLog = nullptr;
static QFile g_logFile;
static bool g_bLog = false;
static QString g_qsLogPath = "";

DTLog::DTLog() {}

DTLog::~DTLog() { qDebug() << "~DTLog()"; }

DTLog *DTLog::getLog() {
  if (g_pLog == NULL) {
    g_pLog = new DTLog;
  }
  return g_pLog;
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
    if(isNeedDebug)
    {
        qDebug() << "[LOG_INFO]: " << qsMsg ;
    }
    static QMessageLogContext qlc;
    logMsg(type,qlc,qsMsg);
}

void DTLog::logMsg(QtMsgType type,const QMessageLogContext &context,const QString &qsMsg) {
  if (g_bLog == false)
  {
      return;
  }
  static QMutex mutex;
  mutex.lock();
  QString text;
  switch (type) {
  case QtDebugMsg:
    text = QString("level:DEBUG");
    break;
  case QtInfoMsg:
    text = QString("level:INFO");
    break;

  case QtWarningMsg:
    text = QString("level:WARN");
    break;

  case QtCriticalMsg:
    text = QString("level:CRITICAL");
    break;

  case QtFatalMsg:
    text = QString("level:FATAL");
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
    //QString current_date = QString("%1").arg(current_date_time);
    //QString message = QString("%3 %1 %2").arg(text).arg(msgNew).arg(current_date);
    QString message = QString("%1 %2 %3").arg(current_date_time).arg(text).arg(msgNew);
    // feat: 参考WeChat Log格式
    //QString message = QString("%1 %2").arg(current_date).arg(msgNew);
#ifdef Q_OS_WIN
    printf(message.toStdString().c_str());
#endif
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
}

void DTLog::functionEnd(const QString &qsFunctionName)
{
    //todo
}
