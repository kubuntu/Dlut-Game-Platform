#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QShowEvent>
#include <QMessageBox>

#include <ClientRequest/JRequestInformation>
#include <Socket/JMainClientSocket>
#include <Session/JSession>

#include "jdialogupdateuserinfo.h"
#include "jdialogstartgame.h"
#include "jdialogchangepassword.h"
#include "service/jinstalledappmanager.h"
#include "service/jgameclientloader.h"
#include "pseudoserver/jpseudoserver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_requestGameInfo=new JRequestInformation<JGameInfo>(this);
    m_requestGameInfo->setObjectName(tr("gameinfosrv"));
	m_currentId=-1;
    ui->setupUi(this);

	m_requestUserInfo=new JRequestInformation<JUserInfo>(this);
	connect(JMainClientSocket::getInstance(),
			SIGNAL(disconnected()),
			SLOT(On_socket_disconnected()));
	m_requestGameList = new JRequestInformation<JGameList>(this);
	
	on_btn_refresh_list_clicked();
	on_btn_refresh_myuserinfo_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_refresh_list_clicked()
{
    ui->list_game->clear();
    ui->widget_gameinfo->clear();
	m_currentId=-1;
	updateGameList();
}

void MainWindow::On_socket_disconnected()
{
	QMessageBox::critical(this,
						  tr("network disconnected"),
						  tr("network disconnected."));
}

void MainWindow::on_list_game_itemClicked(QListWidgetItem* item)
{
	JGameList gl = m_requestGameList->pullInformation(0,1000);
	foreach(const QString& name,gl)
    {
		if(item->text()==name)
        {
			m_currentId=gl.key(name);
            break;
        }
	}
	updateGameInfo(m_currentId);
}

void MainWindow::updateGameList()
{
	JGameList gl = m_requestGameList->pullInformation(0,1000);
	foreach(const QString& name,gl)
	{
		ui->list_game->addItem(name);
	}
}

void MainWindow::updateGameInfo(JID gameId)
{
	JGameInfo gi=m_requestGameInfo->pullInformation(gameId);
	ui->widget_gameinfo->setGameInfo(gi);
	JUserInfo author=m_requestUserInfo->pullInformation(gi.getAuthor());
	if( -1 == author.getUserId() ){
		author = JUserInfo(gi.getAuthor() );
	}
	ui->widget_gameinfo->setUserInfo(author);
}

void MainWindow::on_btn_start_game_clicked()
{
	if(m_currentId<0)
	{
		QMessageBox::warning(this,
							 tr("no game selected!"),
							 tr("please select a game.")
							 );
		return;
	}
	
	JID gameId = m_currentId ;
	JGameInfo gameinfo = m_requestGameInfo->pullInformation(gameId);
	
	JRequestInformation<JServerInfo> rsi ;
	JServerInfo serverinfo = rsi.pullInformation(gameinfo.getServerId());
	JInstalledAppManager* iam = JInstalledAppManager::getInstance() ;
	if( iam->isInstalled(gameId) ){
		PackageMetainfo metainfo = iam->getMetainfo(gameId) ;
		if( metainfo.gameId() == gameId && JVersion::fromString( metainfo.version() ) == gameinfo.getVersion() ){
			JGameClientLoader gameClientLoader;
			gameClientLoader.setParent(parent());
			gameClientLoader.setPseudoServer(SHost(QHostAddress::LocalHost,JPseudoServer::getInstance()->serverPort()));
			gameClientLoader.setGameInfo(gameinfo);
			gameClientLoader.setServerInfo(serverinfo);
			gameClientLoader.setSession(JMainClientSocket::getInstance()->getSession());
			gameClientLoader.start();
			return ;
		}
	}
	JDialogStartGame dlg(this);
	dlg.setGameId(m_currentId);
	dlg.exec();
}

void MainWindow::on_btn_refresh_myuserinfo_clicked()
{
	JID myUserID = JMainClientSocket::getInstance()->getSession()->getUserId();
	JUserInfo userInfo = m_requestUserInfo->pullInformation(myUserID);
	if(userInfo.getUserId() > 0){
		m_myUserInfo = userInfo ;
	}else{
		m_myUserInfo = JUserInfo(myUserID);
	}
	ui->text_userid->setText(QString::number(m_myUserInfo.getUserId()));
	ui->text_nickname->setText(m_myUserInfo.getNickname());
	ui->text_organization->setText(m_myUserInfo.getOrganization());
}

void MainWindow::on_btn_update_myuserinfo_clicked()
{
	JDialogUpdateUserInfo dlg(this);
	dlg.setInitUserInfo(m_myUserInfo);
	if(QDialog::Accepted == dlg.exec()){
		on_btn_refresh_myuserinfo_clicked();
	}
}

void MainWindow::on_btn_changepswd_clicked()
{
	JDialogChangePassword dlg(this);
	dlg.setUserId(m_myUserInfo.getUserId());
	dlg.exec();
}
