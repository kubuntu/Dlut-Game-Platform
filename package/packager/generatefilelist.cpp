#include "generatefilelist.h"

#include "jargumentanalysis.h"

#include <QDir>

GenerateFileList::GenerateFileList()
{
}

void GenerateFileList::generate(){
    JArgumentAnalysis* aa = JArgumentAnalysis::getInstance();
    generateDir(aa->path(),"");
}

QStringList GenerateFileList::fileList()const{
    return m_file.keys();
}

QString GenerateFileList::inZipPath(const QString& filePath)const{
    return m_file.value(filePath);
}

/*!
    \a basePath tail nothing .\n
    \a innerPath head and tail with nothing .
*/
void GenerateFileList::generateDir(const QString& basePath,const QString& innerPath){
    JArgumentAnalysis* aa = JArgumentAnalysis::getInstance();
    if(innerPath == "dgppkg" && aa->isEscapeDgppkg()){
        return ;
    }
    QString baseDirPath ;
    if(innerPath.isEmpty()){
        baseDirPath = basePath ;
    }else{
        baseDirPath = basePath + '/' + innerPath ;
    }
    QDir base = QDir::cleanPath(baseDirPath);

    QFileInfoList list=base.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    foreach(QFileInfo info,list){
        QString in ;
        if(innerPath.isEmpty()){
            in = info.fileName();
        }else{
            in = innerPath + '/' + info.fileName() ;
        }
        if(info.isDir()){
            generateDir(basePath,in );
        }else{
            m_file.insert(info.path() + "/" + info.fileName(),in);
        }
    }
}
