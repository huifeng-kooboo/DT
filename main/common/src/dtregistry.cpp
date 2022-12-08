#include "dtregistry.h"

//implement

DTRegistry::DTRegistry()
{

}

DTRegistry::~DTRegistry()
{

}

DTRegistry& DTRegistry::getInstance() {
    static DTRegistry reg;
    return  reg;
}

bool DTRegistry::setDefaultName(const QString &qsDefaultName) {
  m_qsDefaultName = qsDefaultName;
  return true;
}

bool DTRegistry::getValue(const QString &qsKey, QString &qsValue) {
    QSettings appSettings(m_qsDefaultName);
    QVariant qvValue = appSettings.value(qsKey,"");
    qsValue = qvValue.toString();
   return true;
}

bool DTRegistry::getValue(const QString &qsDefaultName, const QString &qsKey,
                          QString &qsValue) {
    QSettings appSettings(qsDefaultName);
    QVariant qvValue = appSettings.value(qsKey,"");
    qsValue = qvValue.toString();
  return true;
}

bool DTRegistry::setValue(const QString &qsKey, const QString &qsValue) {
    QSettings appSettings(m_qsDefaultName);
    appSettings.setValue(qsKey,qsValue);
    return true;
}

bool DTRegistry::setValue(const QString &qsDefaultName, const QString &qsKey,
                          const QString &qsValue) {
    QSettings appSettings(qsDefaultName);
    appSettings.setValue(qsKey,qsValue);
  // todo
  return true;
}
