#include "generatefilelist.h"

#include <QSettings>

GenerateFileList::GenerateFileList()
{
}

void GenerateFileList::generate(){
    QSettings set("dgppkg.ini",QSettings::IniFormat);

    set.beginGroup("filelist");

    QStringList fileList = set.allKeys();

    foreach(QString file , fileList){
        QString inZipPath = set.value(file).toString();
        m_file.insert(file,inZipPath);
    }
}

QStringList GenerateFileList::fileList()const{
    return m_file.keys();
}

QString GenerateFileList::inZipPath(const QString& filePath)const{
    return m_file.value(filePath);
}
