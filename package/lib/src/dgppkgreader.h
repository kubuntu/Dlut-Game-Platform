#ifndef DGPPKGREADER_H
#define DGPPKGREADER_H

#include "dgppkgbase.h"

class DgpPkgReader : public DgpPkgBase
{
public:
    DgpPkgReader(const QString& filePath);
    PackageMetainfo read()const;
    
    bool extractTo(const QString& dirPath);
protected:
    QFlags<zipobject::OpenModeFlag> getOpenModeFlag()const;
};

#endif // DGPPKGREADER_H
