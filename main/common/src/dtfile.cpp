#include "dtfile.h"
#include "dtlog.h"

bool DTFile::createFile(const QString &qsFilePath, bool bReload)
{
    if(QFile::exists(qsFilePath))
    {
        Logger->logMsg(QtMsgType::QtInfoMsg,QString("%1 File Created.").arg(qsFilePath));
        if(bReload)
        {
            QFile::remove(qsFilePath);
            QFile files(qsFilePath);
            return true;
        }
        else{
            return true;
        }
    }
    QFile file(qsFilePath);
    if(!file.exists())
    {
        Logger->logMsg(QtMsgType::QtFatalMsg, QString("%1 file is create error").arg(qsFilePath));
        return false;
    }

    return true;
}

bool DTFile::deleteFile(const QString &qsFilePath)
{
    if(QFile::exists(qsFilePath))
    {
        return  QFile::remove(qsFilePath);
    }
    return true;
}

bool DTFile::createFolder(const QString &qsFolder, bool bReload)
{
    QDir dir(qsFolder);
    if(!dir.exists())
    {
        Logger->logMsg(QtMsgType::QtInfoMsg,QString("创建文件夹:%1").arg(qsFolder));
        return dir.mkdir(qsFolder);
    }
    if(bReload)
        return true;
    return true;
}

bool DTFile::deleteFolder(const QString &qsFolder){
    if (qsFolder.isEmpty()){
        return false;
    }
    QDir dir(qsFolder);
    if(!dir.exists()){
        return true;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo file, fileList){
        if (file.isFile()){
            file.dir().remove(file.fileName());
        }else{
            deleteFolder(file.absoluteFilePath());
        }
    }
    return dir.rmdir(dir.absolutePath());
}
