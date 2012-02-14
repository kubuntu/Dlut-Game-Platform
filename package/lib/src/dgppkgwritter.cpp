#include "dgppkgwritter.h"

#include "zipobject.h"

#include <QDataStream>

DgpPkgWritter::DgpPkgWritter(const QString& filePath)
    :DgpPkgBase(filePath){
}

bool DgpPkgWritter::writeMetainfo(const PackageMetainfo& info){
    QByteArray data;
    data = PackageMetainfo::toXML(info);
    return m_zip->writeData(data,metainfoPath());
}

bool DgpPkgWritter::writePermissionList(const QMap<QString,int> & list){
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream<<list;
    return m_zip->writeData(data,permissionListPath() );
}

bool DgpPkgWritter::addFile(const QString& filePath,const QString& inZipPath){
    return m_zip->addFile(filePath,inZipPath);
}

QFlags<zipobject::OpenModeFlag> DgpPkgWritter::getOpenModeFlag()const{
    return zipobject::Create;
}
