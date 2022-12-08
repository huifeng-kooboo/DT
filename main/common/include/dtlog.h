#ifndef DTLOG_H
#define DTLOG_H

// 最大日志数量，默认10，超过删除
#define MAX_LOGS_NUM 10
#define DTLOG_PATH_FILENAME "%1_%2.log"
#define Logger DTLog::getLog()

class DTLog {
public:
  DTLog();
  ~DTLog();
  static DTLog *getLog();

  // Log---Basic
  static void logMsg(QtMsgType type,const QString&qsMsg);
  static void logMsg(QtMsgType type,const QMessageLogContext &context,const QString &qsMsg);

  // todo Log---Performance
  void functionStart(const QString &qsFunctionName);
  void functionEnd(const QString &qsFunctionName);

  // LogPath
  static bool createLogPath(const QString &qsSubPath,
                            const QString &qsFileName);
};

#endif // DTLOG_H
