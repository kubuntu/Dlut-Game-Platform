#ifndef DGPPKGBASE_H
#define DGPPKGBASE_H

#include "zipobject.h"
#include "packagemetainfo.h"

class DgpPkgBase
{
public:
    DgpPkgBase(const QString& filePath);
    bool open();
    bool close();

    static QString dgppkgPath();
    static QString metainfoPath();

    virtual ~DgpPkgBase();
protected:
    virtual QFlags<zipobject::OpenModeFlag> getOpenModeFlag()const=0;
protected:
    zipobject* m_zip;
};

#endif // DGPPKGBASE_H
