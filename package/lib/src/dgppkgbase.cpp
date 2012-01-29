#include "dgppkgbase.h"

DgpPkgBase::DgpPkgBase(const QString& filePath)
{
    m_zip = new zipobject(filePath);
}

bool DgpPkgBase::open(){
    return m_zip->open(getOpenModeFlag());
}

bool DgpPkgBase::close(){
    return m_zip->close();
}

QString DgpPkgBase::dgppkgPath(){
    return "dgppkg";
}

QString DgpPkgBase::metainfoPath(){
    return dgppkgPath()+"/metainfo.xml";
}

DgpPkgBase::~DgpPkgBase(){
    delete m_zip;
    m_zip = NULL;
}
