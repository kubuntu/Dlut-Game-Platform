#ifndef PACKAGEMETAINFO_H
#define PACKAGEMETAINFO_H

#include <QByteArray>
#include <QString>

class PackageMetainfo
{
public:
    PackageMetainfo();

    void setGameId(int);
    void setName(const QString&);
    void setVersion(const QString&);
    void setAuthor(const QString&);
    void setOrganization(const QString&);
    void setIntroduction(const QString&);

    static PackageMetainfo fromXML(const QByteArray& data);
    static QByteArray toXML(const PackageMetainfo& info);
private:
    int m_gameId;
    QString m_name;
    QString m_version;
    QString m_author;
    QString m_organization;
    QString m_introduction;
};

#endif // PACKAGEMETAINFO_H
