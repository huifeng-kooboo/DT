#ifndef DTJSON_H
#define DTJSON_H

#define JSON DTJson::getInstance()

/**
  * @brief: Json结构体的封装
  *
*/
class DTJson {
public:
  bool readJsonByFile(const QString &qsFilePath, QJsonDocument &qsJsonDocument);
  bool readJsonStr(const QString &qsJsonStr, QJsonDocument &qsJsonDocument);
  bool writeJsonToFile(const QString &qsJsonStr, const QString &qsFilePath);
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
private:
  DTJson();
};

#endif // DTJSON_H
