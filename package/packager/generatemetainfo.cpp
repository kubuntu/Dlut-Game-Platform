#include "generatemetainfo.h"

#include <QSettings>
#include <QFile>

GenerateMetainfo::GenerateMetainfo()
{
}

PackageMetainfo GenerateMetainfo::generate(){
    QSettings set("dgppkg.ini",QSettings::IniFormat);

    QString inputPath = set.value("input/path",".").toString();
    QString metainfoPath = set.value("metainfo/path","dgppkg/metainfo.xml").toString();

    QFile file(inputPath+'/'+metainfoPath);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();

    PackageMetainfo info = PackageMetainfo::fromXML(data);

    return info;
}
