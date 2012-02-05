#include "generatefilelist.h"

#include "jargumentanalysis.h"

#include <QDir>

GenerateFileList::GenerateFileList()
{
}

void GenerateFileList::generate(){
    JArgumentAnalysis* aa = JArgumentAnalysis::getInstance();
    generateDir(aa->path(),"/");
}

QStringList GenerateFileList::fileList()const{
    return m_file.keys();
}

QString GenerateFileList::inZipPath(const QString& filePath)const{
    return m_file.value(filePath);
}

/*!
    \a basePath tail nothing .\n
    \a innerPath head and tail with '/' .
*/
void GenerateFileList::generateDir(const QString& basePath,const QString& innerPath){
    JArgumentAnalysis* aa = JArgumentAnalysis::getInstance();
    if(innerPath == "/dgppkg/" && aa->isEscapeDgppkg()){
        return ;
    }
    QDir base = QDir::cleanPath(basePath + innerPath);

    QFileInfoList list=base.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    foreach(QFileInfo info,list){
        QString in = innerPath + info.fileName();
        if(info.isDir()){
            generateDir(basePath,in+'/');
        }else{
            m_file.insert(info.path() + "/" + info.fileName(),in);
        }
    }
}
