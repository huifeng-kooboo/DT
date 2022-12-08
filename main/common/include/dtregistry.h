#ifndef DTREGISTRY_H
#define DTREGISTRY_H

// 注册表
#define REG DTRegistry::getInstance()

// 注册表相关的操作
class DTRegistry{
public:
    DTRegistry();
    ~DTRegistry();
    static DTRegistry &getInstance();
    bool setDefaultName(const QString& qsDefaultName);

    bool setValue(const QString&qsKey,const QString&qsValue);
    bool getValue(const QString&qsKey,QString&qsValue);

    bool setValue(const QString&qsDefaultName,const QString&qsKey,const QString&qsValue);
    bool getValue(const QString&qsDefaultName,const QString&qsKey,QString&qsValue);
private:
    QString m_qsDefaultName; //

};

#endif // DTREGISTRY_H
