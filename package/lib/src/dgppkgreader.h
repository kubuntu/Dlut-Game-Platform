#ifndef DGPPKGREADER_H
#define DGPPKGREADER_H

#include "dgppkgbase.h"

#include <QMap>

class DgpPkgReader : public DgpPkgBase
{
public:
    DgpPkgReader(const QString& filePath);
    PackageMetainfo readMetainfo()const;
    QMap<QString,int> readPermissionList()const;
    
    bool extractTo(const QString& dirPath);
protected:
    QFlags<zipobject::OpenModeFlag> getOpenModeFlag()const;
};

#endif // DGPPKGREADER_H
