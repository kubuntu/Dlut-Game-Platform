#include <QtCore/QCoreApplication>

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

    GenerateMetainfo gm;
    PackageMetainfo info = gm.generate();

    GenerateFileList gf;
    gf.generate();

    DgpPkgWritter writter("try.dgp");
    writter.open();
    writter.write(info);

    QStringList fileList = gf.fileList();
    JArgumentAnalysis* aa = JArgumentAnalysis::getInstance();
    const QList<QRegExp>& ignoreList = aa->ignoreList();
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
        }
    }

    writter.close();
    return 0;
}
