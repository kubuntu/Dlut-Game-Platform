#include "dgppkgreader.h"

DgpPkgReader::DgpPkgReader(const QString& filePath)
    :DgpPkgBase(filePath){
}

PackageMetainfo DgpPkgReader::read()const{
    QByteArray data;
    data = m_zip->readData(metainfoPath());
    return PackageMetainfo::fromXML(data);
}

bool DgpPkgReader::extractTo(const QString& dirPath){
    return m_zip->extractTo(dirPath);
}

QFlags<zipobject::OpenModeFlag> DgpPkgReader::getOpenModeFlag()const{
    return 0;
}
