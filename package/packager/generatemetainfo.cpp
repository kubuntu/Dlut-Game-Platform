#include "generatemetainfo.h"

#include "jargumentanalysis.h"

#include <QFile>

GenerateMetainfo::GenerateMetainfo()
{
}

PackageMetainfo GenerateMetainfo::generate(){
    JArgumentAnalysis* aa = JArgumentAnalysis::getInstance();

    QString filePath = aa->path()+"/dgppkg/metainfo.xml";

    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();

    PackageMetainfo info = PackageMetainfo::fromXML(data);

    return info;
}
