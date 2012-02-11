#ifndef PACKAGEMETAINFO_H
#define PACKAGEMETAINFO_H

#include <QByteArray>
#include <QString>

class PackageMetainfo
{
public:
    PackageMetainfo();

    enum OS{
        X11,
        SBMSWIN,
        MAX,
    };

    void setGameId(int);
    void setName(const QString&);
    void setVersion(const QString&);
    void setAuthor(const QString&);
    void setOrganization(const QString&);
    void setIntroduction(const QString&);
    void setOS(OS os);
    void setOsStr(const QString&);
    void setRunFilePath(const QString&);

    int gameId()const;
    const QString& name()const;
    const QString& version()const;
    OS os()const;
    const QString& osStr()const;
    const QString& runFilePath()const;

    static PackageMetainfo fromXML(const QByteArray& data);
    static QByteArray toXML(const PackageMetainfo& info);
private:
    int m_gameId;
    QString m_name;
    QString m_version;
    QString m_author;
    QString m_organization;
    QString m_introduction;
    OS m_os;
    QString m_runFilePath;
};

#endif // PACKAGEMETAINFO_H
