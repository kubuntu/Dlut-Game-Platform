#include "jformaddgame.h"
#include "ui_jformaddgame.h"

#include <ClientRequest/JUploadGameInfo>
#include <ClientRequest/JUploadServerInfo>
#include <DataStruct/JGameInfo>
#include <DataStruct/JServerInfo>
#include <Global/CodeError>

JFormAddGame::JFormAddGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JFormAddGame)
{
    ui->setupUi(this);
	connect(ui->btn_game_reset,SIGNAL(clicked()),SLOT(reset()));
}

JFormAddGame::~JFormAddGame()
{
    delete ui;
}

void JFormAddGame::reset()
{
	ui->edt_authorid->clear();
	ui->edt_downloadurl->clear();
	ui->edt_gameid->clear();
	ui->edt_gamename->clear();
	ui->edt_intro->clear();
	ui->edt_runnerid->clear();
	ui->edt_serverid->clear();
	ui->edt_servername->clear();
	ui->edt_server_addr->clear();
	ui->edt_server_port->clear();
	ui->edt_version->clear();
}

void JFormAddGame::on_btn_game_add_clicked()
{
	JGameInfo gameinfo(
			ui->edt_gameid->text().toInt(),
			ui->edt_gamename->text(),
			JVersion(ui->edt_version->text().toInt()),
			ui->edt_authorid->text().toInt(),
			ui->edt_runnerid->text().toInt(),
			ui->edt_intro->text(),
			ui->edt_serverid->text().toInt(),
			QUrl(ui->edt_downloadurl->text())
			);
	ui->txt_msg_add_game->append(tr("begin send game info"));
	JUploadGameInfo ugi;
	JCode cugi = ugi.pushGameInfo(gameinfo,1000);
	if(ESuccess == cugi){
		ui->txt_msg_add_game->append(tr("send game info success"));
	}else{
		ui->txt_msg_add_game->append(tr("send game failed : %1").arg(cugi));
		return ;
	}
	JServerInfo serverinfo(
			ui->edt_serverid->text().toInt(),
			ui->edt_servername->text(),
			ui->edt_runnerid->text().toInt(),
			SHost(
				QHostAddress(ui->edt_server_addr->text()),
				ui->edt_server_port->text().toInt()
				)
			);
	ui->txt_msg_add_game->append(tr("begin send server info"));
	JUploadServerInfo usi;
	JCode cusi = usi.pushServerInfo(serverinfo,1000);
	if(ESuccess == cusi){
		ui->txt_msg_add_game->append(tr("send server info success"));
	}else{
		ui->txt_msg_add_game->append(tr("send server info failed : %1").arg(cusi));
	}
}
