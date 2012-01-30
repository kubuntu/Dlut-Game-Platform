#ifndef DGPPKGWRITTER_H
#define DGPPKGWRITTER_H

#include "dgppkgbase.h"

class DgpPkgWritter : public DgpPkgBase
{
public:
    DgpPkgWritter(const QString& filePath);
    bool write(const PackageMetainfo& info);
    bool addFile(const QString& filePath,const QString& inZipPath);
protected:
    QFlags<zipobject::OpenModeFlag> getOpenModeFlag()const;
};

#endif // DGPPKGWRITTER_H
