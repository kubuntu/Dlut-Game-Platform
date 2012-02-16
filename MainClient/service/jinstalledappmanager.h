#ifndef JINSTALLEDAPPMANAGER_H
#define JINSTALLEDAPPMANAGER_H

#include <QObject>

#include <Global/Global>

#include <PackageMetainfo>

class QSettings;

class JInstalledAppManager : public QObject
{
    Q_OBJECT
public:
	static JInstalledAppManager* getInstance();
	void setInstallPath(JID gameId,const QString& path);
	QString getInstallPath(JID gameId)const;
	PackageMetainfo getMetainfo(JID gameId)const;
	QString getRunFilePath(JID gameId)const;
	bool isInstalled(JID gameId)const;
private:
    explicit JInstalledAppManager(QObject *parent = 0);
	QString key(JID gameId)const;
	QSettings* m_settings;
};

#endif // JINSTALLEDAPPMANAGER_H
