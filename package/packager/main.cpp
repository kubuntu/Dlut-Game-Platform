#include <QtCore/QCoreApplication>
#include <QFile>

#include <DgpPkgWritter>
#include <QDebug>

#include "generatemetainfo.h"
#include "generatefilelist.h"
#include "jargumentanalysis.h"

/*!
    usage :
        package path
        -i reg : ignore by reg
*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // meta info
    GenerateMetainfo gm;
    PackageMetainfo info = gm.generate();

    // file list
    GenerateFileList gf;
    gf.generate();

    // file name
    QString fileName = QString("%1_%2_%3.dgp")
            .arg(info.name())
            .arg(info.version())
            .arg(info.osStr());

    // writter
    DgpPkgWritter writter(fileName);
    writter.open();
    writter.writeMetainfo(info);

    // file list
    QStringList fileList = gf.fileList();
    JArgumentAnalysis* aa = JArgumentAnalysis::getInstance();
    const QList<QRegExp>& ignoreList = aa->ignoreList();
    
    // file permissions list
    QMap<QString,int> pmsnList ;
    foreach(QString filePath , fileList){
        QString inZipPath = gf.inZipPath(filePath);
        bool ignore = false;
        foreach(QRegExp reg , ignoreList){
            if(inZipPath.contains(reg)){
                ignore = true ;
                break;
            }
        }

        if( !ignore ){
            qDebug()<<filePath<<inZipPath;
            
            writter.addFile(filePath,inZipPath);
            pmsnList.insert(inZipPath , QFile::permissions(filePath) );
        }
    }
    qDebug()<<pmsnList ;
    writter.writePermissionList(pmsnList);

    writter.close();
    return 0;
}
