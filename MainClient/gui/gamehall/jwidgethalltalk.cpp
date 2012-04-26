#include "jwidgethalltalk.h"
#include "ui_jwidgethalltalk.h"

#include <Processor/JClientHallTalkProcessor>
#include <Socket/JMainClientSocket>
#include <Session/JSession>
#include <ClientRequest/JRequestInformation>

JWidgetHallTalk::JWidgetHallTalk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JWidgetHallTalk)
{
	m_processor = JClientHallTalkProcessor::getInstance();
	m_requserinfo = new JRequestInformation<JUserInfo>(this);
    ui->setupUi(this);
	connect(m_processor,SIGNAL(rcvMessage(QString)),SLOT(showMessage(QString)));
	connect(ui->lineEdit,SIGNAL(returnPressed()),SLOT(sendMessageInEdit()));
	connect(ui->btn_send,SIGNAL(clicked()),SLOT(sendMessageInEdit()));
	connect(ui->btn_clear,SIGNAL(clicked()),ui->textBrowser,SLOT(clear()));
}

JWidgetHallTalk::~JWidgetHallTalk()
{
    delete ui;
}

void JWidgetHallTalk::showMessage(const QString& msg)
{
	ui->textBrowser->append(msg);
}

void JWidgetHallTalk::sendMessageInEdit()
{
	JID myUserID = JMainClientSocket::getInstance()->getSession()->getUserId();
	JUserInfo myUserInfo = m_requserinfo->getInformation(myUserID);
	QString nickname ;
	if(myUserInfo.getNickname().isEmpty()){
		nickname = tr("no nickname(%1)").arg(myUserID);
	}else{
		nickname = myUserInfo.getNickname() ;
	}
	QString msg=tr("%1 says:%2").arg(nickname).arg(ui->lineEdit->text());
	m_processor->sendMessage(msg);
	ui->lineEdit->clear();
}
