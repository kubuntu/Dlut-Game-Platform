#include "dgppkgreader.h"

#include <QDataStream>

DgpPkgReader::DgpPkgReader(const QString& filePath)
    :DgpPkgBase(filePath){
}

PackageMetainfo DgpPkgReader::readMetainfo()const{
    QByteArray data;
    data = m_zip->readData(metainfoPath());
    return PackageMetainfo::fromXML(data);
}

QMap<QString,int> DgpPkgReader::readPermissionList()const{
    QByteArray data;
    data = m_zip->readData(permissionListPath() );
    QDataStream stream(data);
    QMap<QString,int> rtn;
    stream>>rtn;
    return rtn;
}

bool DgpPkgReader::extractTo(const QString& dirPath){
    return m_zip->extractTo(dirPath);
}

QFlags<zipobject::OpenModeFlag> DgpPkgReader::getOpenModeFlag()const{
    return 0;
}
