#include "jinstalledappmanager.h"

#include <DgpPkgReader>

#include <QFile>
#include <QSettings>
#include <QDir>

JInstalledAppManager* JInstalledAppManager::getInstance(){
	static JInstalledAppManager* s_instance = NULL ;
	if( NULL == s_instance ){
		static QObject parent ;
		s_instance = new JInstalledAppManager(&parent);
	}
	return s_instance ;
}

void JInstalledAppManager::setInstallPath(JID gameId,const QString& path){
	m_settings->setValue(key(gameId),path);
}

QString JInstalledAppManager::getInstallPath(JID gameId)const{
	return m_settings->value(key(gameId)).toString();
}

PackageMetainfo JInstalledAppManager::getMetainfo(JID gameId)const{
	QString filePath = QString("%1/%2")
					   .arg(getInstallPath(gameId))
					   .arg(DgpPkgBase::metainfoPath());
	QFile file(filePath);
	file.open(QIODevice::ReadOnly);
	QByteArray data = file.readAll();

	PackageMetainfo info = PackageMetainfo::fromXML(data);

	return info;
}

QString JInstalledAppManager::getRunFilePath(JID gameId)const{
	PackageMetainfo info = getMetainfo(gameId);

	QString runFilePath = QString("./%1")
						  .arg(info.runFilePath());
	return runFilePath ;
}

bool JInstalledAppManager::isInstalled(JID gameId)const{
	return m_settings->contains(key(gameId));
}

JInstalledAppManager::JInstalledAppManager(QObject *parent) :
    QObject(parent)
{
	m_settings = new QSettings("installedapp.ini",QSettings::IniFormat,this);
}

QString JInstalledAppManager::key(JID gameId)const{
	return QString("apps/%1").arg(gameId);
}
