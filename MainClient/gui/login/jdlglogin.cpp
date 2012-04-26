#include "jdlglogin.h"
#include "ui_jdlglogin.h"

#include "jdialoguserregister.h"

#include <ClientRequest/JRequestLogin>
#include <Global/Login>
#include <Socket/JMainClientSocket>

#include <QMessageBox>

JDlgLogin::JDlgLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JDlgLogin)
{
	m_rqslogin=new JRequestLogin(this);
	m_rqslogin->setObjectName("rqsloginsrv");
    ui->setupUi(this);
    ui->edt_username->setText(m_remember.getUserName());
    ui->edt_passwd->setText(m_remember.getPassWord());
    ui->chb_rememberpassword->setChecked(m_remember.getIsRemember());
    ui->chb_autologin->setChecked(m_remember.getIsAutoLogin());
	ui->cb_role->setCurrentIndex(m_remember.getRole());
	connect(this,SIGNAL(autoLogin()),this,SLOT(accept()),Qt::QueuedConnection);
    connect(this,SIGNAL(autoLogin()),this,SLOT(accept()),Qt::QueuedConnection);
	connect(JMainClientSocket::getInstance(),
			SIGNAL(disconnected()),
			SLOT(On_socket_disconnected()));
}

JDlgLogin::~JDlgLogin()
{
    delete ui;
}

void JDlgLogin::accept()
{
    if(ui->edt_username->text().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("username is empty"),
                              tr("username can not be empty!")
                              );
        return;
    }
    if(ui->edt_passwd->text().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("password is empty"),
                              tr("password can not be empty!")
                              );
        return;
    }
    m_remember.setIsRemember(ui->chb_rememberpassword->isChecked());
    m_remember.setIsAutoLogin(ui->chb_autologin->isChecked());
    if(ui->chb_rememberpassword->isChecked())
    {
        m_remember.remember();
    }else{
		m_remember.remember();
        m_remember.remove();
	}
	m_rqslogin->login(ui->edt_username->text(),
					  ui->edt_passwd->text(),
					  (ERole)ui->cb_role->currentIndex());
	ui->lab_message->setText(tr("begin to login"));
	if(!m_rqslogin->waitForLogined(1000))
	{
		ui->lab_message->setText(tr("login failed : %1").arg(m_rqslogin->getLoginError()));
		return;
	}
	done(QDialog::Accepted);
}

void JDlgLogin::error(QAbstractSocket::SocketError e)
{
    qDebug()<<e;
    ui->lab_message->setText(tr("error"));
}

void JDlgLogin::on_edt_username_editingFinished()
{
    m_remember.changeUserName(ui->edt_username->text());
    ui->edt_passwd->setText(m_remember.getPassWord());
}

void JDlgLogin::On_socket_disconnected()
{
	QMessageBox::critical(this,
						  tr("network disconnected"),
						  tr("network disconnected."));
}

void JDlgLogin::on_edt_passwd_editingFinished()
{
    m_remember.setPassWord(ui->edt_passwd->text());
}

void JDlgLogin::on_cb_role_currentIndexChanged(int index)
{
	m_remember.setRole(index);
}

void JDlgLogin::on_btn_register_clicked()
{
	JDialogUserRegister dlg(this);
	dlg.exec();
}
