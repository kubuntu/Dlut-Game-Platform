#ifndef JARGUMENTANALYSIS_H
#define JARGUMENTANALYSIS_H

#include <QObject>

#include <QList>
#include <QRegExp>

class JArgumentAnalysis : public QObject
{
public:
    static JArgumentAnalysis* getInstance();
    const QString& path()const;
    const QList<QRegExp>& ignoreList()const;
    bool isEscapeDgppkg()const;
private:
    explicit JArgumentAnalysis(QObject *parent = 0);
    static JArgumentAnalysis* s_instance ;
    void analysis();
    QString m_path ;
    QList<QRegExp> m_ignoreList ;
};

#endif // JARGUMENTANALYSIS_H
