#ifndef GENERATEFILELIST_H
#define GENERATEFILELIST_H

#include <QStringList>
#include <QMap>

class GenerateFileList
{
public:
    GenerateFileList();
    void generate();
    QStringList fileList()const;
    QString inZipPath(const QString& filePath)const;
private:
    void generateDir(const QString& basePath,const QString& innerPath);
    QMap<QString,QString> m_file;
};

#endif // GENERATEFILELIST_H
