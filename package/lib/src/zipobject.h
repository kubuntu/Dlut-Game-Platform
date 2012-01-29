#ifndef ZIPOBJECT_H
#define ZIPOBJECT_H

#include <QString>

class zip ;
class zipobject{
public:
    zipobject(const QString& filePath);
    ~zipobject();
    void setFilePath(const QString& filePath);
    const QString& filePath()const;

    enum OpenModeFlag{
        Create = 0x01,
        ErrorIfExists = 0x02,
        CheckCons = 0x04,
    };
    bool open(QFlags<OpenModeFlag> flags = 0);

    bool addFile(const QString& filePath,const QString& inZipPath);

    bool writeData(const QByteArray& data,const QString& inZipPath);
    QByteArray readData(const QString& inZipPath)const;

    bool close();

    QString errorString()const;
private:
    static QByteArray getCharPtr(const QString& string);
private:
    QString m_filePath ;
    zip* m_zip ;
};

#endif // ZIPOBJECT_H
