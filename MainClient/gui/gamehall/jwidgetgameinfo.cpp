#include "jwidgetgameinfo.h"
#include "ui_jwidgetgameinfo.h"

#include <DataStruct/JGameInfo>
#include <DataStruct/JUserInfo>

JWidgetGameInfo::JWidgetGameInfo(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::JWidgetGameInfo)
{
	ui->setupUi(this);
	
	ui->labi_authorid->hide();
	ui->labi_authorname->hide();
	ui->labi_authororg->hide();
}

JWidgetGameInfo::~JWidgetGameInfo()
{
	delete ui;
}

void JWidgetGameInfo::clear()
{
	ui->labi_name->clear();
	ui->labi_version->clear();
	ui->labi_intro->clear();
	ui->labi_author->clear();
	ui->labi_authorid->clear();
	ui->labi_authorname->clear();
	ui->labi_authororg->clear();
}

void JWidgetGameInfo::setGameInfo(const JGameInfo& gameinfo)
{
	ui->labi_name->setText( gameinfo.getName() );
	ui->labi_version->setText( gameinfo.getVersion().toString() );
	ui->labi_intro->setText( gameinfo.getIntroduction() );
}
void JWidgetGameInfo::setUserInfo(const JUserInfo& userinfo)
{
	ui->labi_author->setText( userinfo.getNickname() );
	ui->labi_authorid->setText( QString::number(userinfo.getUserId()) );
	ui->labi_authorname->setText( userinfo.getNickname() );
	ui->labi_authororg->setText( userinfo.getOrganization() );
}

void JWidgetGameInfo::on_btn_expand_clicked()
{
	if( ui->labi_author->isVisible() ){
		ui->labi_author->hide();

		ui->labi_authorid->show();
		ui->labi_authorname->show();
		ui->labi_authororg->show();
	}else{
		ui->labi_author->show();

		ui->labi_authorid->hide();
		ui->labi_authorname->hide();
		ui->labi_authororg->hide();
	}
}
