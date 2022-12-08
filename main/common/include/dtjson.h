#ifndef DTJSON_H
#define DTJSON_H

#define JSON DTJson::getInstance()

class DTJson {
public:
  bool readJsonByFile(const QString &qsFilePath, QJsonDocument &qsJsonDocument);
  bool readJsonStr(const QString &qsJsonStr, QJsonDocument &qsJsonDocument);
  bool writeJsonToFile(const QString &qsJsonStr, const QString &qsFilePath);
  // 设置getValue
  bool setValue(QJsonDocument &jsonDocument, const QString &qsKey,
                const QString &qsValue);
  bool getValue(QJsonDocument &jsonDocument, const QString &qsKey,
                QString &qsValue);
  bool saveJsonDocumentToFile(QJsonDocument &jsonDocument,
                              const QString &qsFilePath);
  static DTJson &getInstance() {
    static DTJson dtJson;
    return dtJson;
  };

#ifdef DEBUG
  void test();
#endif

private:
  DTJson();
};

#endif // DTJSON_H
