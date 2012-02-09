#ifndef JGAMECLIENTLOADER_H
#define JGAMECLIENTLOADER_H

#include <DataStruct/SHost>
#include <DataStruct/JGameInfo>
#include <DataStruct/JServerInfo>

class JDownloader;
class JSession;

class JGameClientLoader
{
public:
    JGameClientLoader();
	~JGameClientLoader();
	void setParent(QObject* parent);
	void setPseudoServer(const SHost& pseudo);
	void setGameInfo(const JGameInfo& gameinfo);
	void setServerInfo(const JServerInfo& serverinfo);
	void setSession(JSession* session);

	JDownloader* getDownloader()const;
	const QString& getErrorString()const;
	void download();
	bool install();
	void start();
private:
	void setErrorString(const QString& error);
	QString getPartialSaveFilePath()const;
	QString getArchiveSaveFilePath()const;
	QString getInstallDirPath()const;
	QString getGameClientFilePath()const;
	QStringList getArguments()const;
private:
	SHost m_pseudoServer;
	JGameInfo m_gameInfo;
	JServerInfo m_serverInfo;
	JDownloader* m_downloader;
	QObject* m_parent;
	JSession* m_session;
	QString m_error;
};

#endif // JGAMECLIENTLOADER_H
