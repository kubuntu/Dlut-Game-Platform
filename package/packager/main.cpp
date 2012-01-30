#include <QtCore/QCoreApplication>

#include <DgpPkgWritter>

#include "generatemetainfo.h"
#include "generatefilelist.h"

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
    foreach(QString filePath , fileList){
        QString inZipPath = gf.inZipPath(filePath);
        writter.addFile(filePath,inZipPath);
    }

    writter.close();
    return 0;
}
