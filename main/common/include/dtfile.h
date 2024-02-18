#ifndef DTFILE_H
#define DTFILE_H

class DTFile{
public:
    static bool createFile(const QString&qsFilePath, bool bReload);
    static bool createFolder(const QString&qsFolder, bool bReload);
    static bool deleteFile(const QString&qsFilePath);
    static bool deleleFolder(const QString&qsFolder);
};
#endif // DTFILE_H
