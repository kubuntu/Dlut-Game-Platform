#include "dgppkgwritter.h"

#include "zipobject.h"

DgpPkgWritter::DgpPkgWritter(const QString& filePath)
    :DgpPkgBase(filePath){
}

bool DgpPkgWritter::write(const PackageMetainfo& info){
    QByteArray data;
    data = PackageMetainfo::toXML(info);
    return m_zip->writeData(data,metainfoPath());
}

bool DgpPkgWritter::addFile(const QString& filePath,const QString& inZipPath){
    return m_zip->addFile(filePath,inZipPath);
}

QFlags<zipobject::OpenModeFlag> DgpPkgWritter::getOpenModeFlag()const{
    return zipobject::Create;
}
