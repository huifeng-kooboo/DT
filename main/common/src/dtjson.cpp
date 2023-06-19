#include "dtjson.h"
#include "dtlog.h"

DTJson::DTJson() {}

bool DTJson::readJsonByFile(const QString &qsFilePath,
                            QJsonDocument &qsJsonDocument) {
    if (QFile::exists(qsFilePath)) {
        QFile file(qsFilePath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        if (!file.isOpen()) {
            Logger->logMsg(QtMsgType::QtSystemMsg, "Json文件打开失败");
            return false;
        }
        QString value = file.readAll();
        file.close();
        QJsonParseError parseJsonErr;
        qsJsonDocument = QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);
        if (parseJsonErr.error != QJsonParseError::NoError) {
            return false;
        }
        return true;
    } else {
        return false;
    }
    return false;
}

bool DTJson::readJsonStr(const QString &qsJsonStr,
                         QJsonDocument &qsJsonDocument) {
    QJsonParseError jsonError;
    QJsonDocument jsonDoc(
                QJsonDocument::fromJson(qsJsonStr.toStdString().data(), &jsonError));
    if (jsonError.error != QJsonParseError::NoError) {
        return false;
    } else {
        qsJsonDocument = jsonDoc;
        return true;
    }
}

bool DTJson::writeJsonToFile(const QString &qsJsonStr,
                             const QString &qsFilePath) {
    QFile file;
    file.setFileName(qsFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))

    {
        QTextStream in(&file);
        in << qsJsonStr << endl;
    }
    file.close();
    return true;
}

bool DTJson::setValue(QJsonDocument &jsonDocument, const QString &qsKey, const QString &qsValue)
{
    QJsonObject qJsonObj = jsonDocument.object();
    qJsonObj.insert(qsKey,qsValue);
    return true;
}

bool DTJson::getValue(QJsonDocument &jsonDocument, const QString &qsKey, QString &qsValue)
{
    QJsonObject qJsonObj = jsonDocument.object();
    qsValue = qJsonObj.value(qsKey).toString();
    return true;
}

bool DTJson::saveJsonDocumentToFile(QJsonDocument &jsonDocument, const QString &qsFilePath)
{
    QByteArray qbArray = jsonDocument.toJson();
    QFile file;
    file.setFileName(qsFilePath);
    //只写 追加写入
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        file.write(qbArray);
    }
    file.close();
    return true;
}
