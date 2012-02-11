#include "jgameclientloader.h"
#include "jdownloader.h"
#include "jinstalledappmanager.h"

#include <Global/CodeError>
#include <Session/JSession>
#include <DgpPkgReader>

#include <QProcess>
#include <QFile>
#include <QFileInfo>

JGameClientLoader::JGameClientLoader()
{
	m_downloader = new JDownloader;
}

JGameClientLoader::~JGameClientLoader()
{
	delete m_downloader;
}

void JGameClientLoader::setParent(QObject* parent)
{
	m_parent = parent;
}

void JGameClientLoader::setPseudoServer(const SHost& pseudo)
{
	m_pseudoServer = pseudo;
}

void JGameClientLoader::setGameInfo(const JGameInfo& gameinfo)
{
	m_gameInfo = gameinfo;
}

void JGameClientLoader::setServerInfo(const JServerInfo& serverinfo)
{
	m_serverInfo = serverinfo;
}

void JGameClientLoader::setSession(JSession* session)
{
	m_session = session;
}

JDownloader* JGameClientLoader::getDownloader()const
{
	return m_downloader;
}

const QString& JGameClientLoader::getErrorString()const
{
	return m_error;
}

void JGameClientLoader::download()
{
	m_downloader->start(
				m_gameInfo.getDownloadUrl(),
				getPartialSaveFilePath());
}

bool JGameClientLoader::install()
{
	// move file from partial to archive
	QFile partialFile (getPartialSaveFilePath());
	if(!partialFile.rename(getArchiveSaveFilePath())){
		m_error = partialFile.errorString();
		return false;
	}
	partialFile.close();

	// read metainfo
	DgpPkgReader reader(getArchiveSaveFilePath());
	reader.open();
	PackageMetainfo metainfo = reader.read();

	// check metainfo
	// - id
	if(metainfo.gameId() != m_gameInfo.getGameId() ){
		m_error =
				QObject::tr("gameinfo not match : id (%1,%2)")
				.arg(metainfo.gameId())
				.arg(m_gameInfo.getGameId());
		return false;
	}
	// - name
	if(metainfo.name() != m_gameInfo.getName()){
		m_error =
				QObject::tr("gameinfo not match : name (%1,%2)")
				.arg(metainfo.name())
				.arg(m_gameInfo.getName());
		return false;
	}
	// - version
	JVersion versionInMetainfo = JVersion::fromString(metainfo.version());
	if(versionInMetainfo != m_gameInfo.getVersion()){
		m_error =
				QObject::tr("gameinfo not match : version (%1,%2)")
				.arg(versionInMetainfo.toString())
				.arg(m_gameInfo.getVersion().toString());
		return false;
	}

	// extract package
	QString dirPath = getInstallDirPath() ;
	if( ! reader.extractTo(dirPath) ){
		m_error = 
				QObject::tr("extract fail .");
		return false;
	}

	// write metainfo to db

	return true;
}

void JGameClientLoader::start()
{
	static QProcess *s_process=NULL;
	if(s_process==NULL)
	{
		s_process=new QProcess(m_parent);
	}
	if(s_process->state()==QProcess::NotRunning)
	{
		QString filePath = getGameClientFilePath();
		qDebug()<<"run:"<<filePath;
		s_process->setProcessChannelMode(QProcess::ForwardedChannels);
		s_process->start(filePath,getArguments());
		if(s_process->waitForStarted(1000)){
			qDebug()<<"run succeed";
		}else{
			qDebug()<<"run failed"<<s_process->errorString();
		}
	}else{
		qDebug()<<"is running.escape";
	}
}

void JGameClientLoader::setErrorString(const QString& error)
{
	m_error = error;
}

QString JGameClientLoader::getPartialSaveFilePath()const
{
	QString fileName ;
	QFileInfo f(m_gameInfo.getDownloadUrl().path());
	fileName = f.fileName();
	qDebug()<<__FUNCTION__<<fileName;
	return QString("temp/partial/%1")
			.arg(fileName);
}

QString JGameClientLoader::getArchiveSaveFilePath()const
{
	QString fileName ;
	QFileInfo f(m_gameInfo.getDownloadUrl().path());
	fileName = f.fileName();
	qDebug()<<__FUNCTION__<<fileName;
	return QString("temp/%1")
			.arg(fileName);
}

QString JGameClientLoader::getInstallDirPath()const
{
	return QString("clients/%1/").arg(m_gameInfo.getGameId());
}

QString JGameClientLoader::getGameClientFilePath()const
{
	JInstalledAppManager* iam = JInstalledAppManager::getInstance();
	return iam->getRunFilePath(m_gameInfo.getGameId());
}

QStringList JGameClientLoader::getArguments()const
{
	QStringList ret;
	ret<<QString::number(m_session->getUserId());
	ret<<m_session->getLoginHashCodeStr();
	ret<<m_pseudoServer.m_address.toString();
	ret<<QString::number(m_pseudoServer.m_port);
	ret<<m_serverInfo.getHost().m_address.toString();
	ret<<QString::number(m_serverInfo.getHost().m_port);
	return ret;
}
