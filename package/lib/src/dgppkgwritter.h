#ifndef DGPPKGWRITTER_H
#define DGPPKGWRITTER_H

#include "dgppkgbase.h"

#include <QMap>

class DgpPkgWritter : public DgpPkgBase
{
public:
    DgpPkgWritter(const QString& filePath);
    bool writeMetainfo(const PackageMetainfo& info);
    bool writePermissionList(const QMap<QString,int> & list);

    bool addFile(const QString& filePath,const QString& inZipPath);
protected:
    QFlags<zipobject::OpenModeFlag> getOpenModeFlag()const;
};

#endif // DGPPKGWRITTER_H
