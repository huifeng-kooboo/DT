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
        return false;
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

//删除文件夹
bool DTFile::deleleFolder(const QString &qsFolder)
{
    if (qsFolder.isEmpty()){
        return false;
    }
    QDir dir(qsFolder);
    if(!dir.exists()){
        return true;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //设置过滤
    QFileInfoList fileList = dir.entryInfoList(); // 获取所有的文件信息
    foreach (QFileInfo file, fileList){ //遍历文件信息
        if (file.isFile()){ // 是文件，删除
            file.dir().remove(file.fileName());
        }else{ // 递归删除
            deleleFolder(file.absoluteFilePath());
        }
    }
    return dir.rmdir(dir.absolutePath()); // 删除文件夹
}
