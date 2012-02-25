#include "jdialogchangepassword.h"
#include "ui_jdialogchangepassword.h"
#include "service/jinputpasswordvalidater.h"

#include <Util/JEncryptor>
#include <Processor/JClientChangePasswordProcessor>

#include <QMessageBox>

JDialogChangePassword::JDialogChangePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JDialogChangePassword)
{
	m_processor = JClientChangePasswordProcessor::getInstance();
    ui->setupUi(this);
	connect(m_processor,
			SIGNAL(receiveResult(JCode)),
			SLOT(receiveResult(JCode)));
}

JDialogChangePassword::~JDialogChangePassword()
{
    delete ui;
}

void JDialogChangePassword::setUserId(JID userId)
{
	m_userId = userId ;
}

void JDialogChangePassword::accept()
{
	if(ui->edt_newpswd->text() != ui->edt_renewpswd->text()){
		QMessageBox::critical(
					this,
					tr("change password error"),
					tr("repeat password not match"));
		return ;
	}

	JInputPasswordValidater ipv;
	if( ! ipv.validatePassword( ui->edt_newpswd->text() ) ){
		QMessageBox::critical(this,
							  tr("input password error"),
							  ipv.getErrorString());
		return ;
	}

	JEncryptor ectr;
	QString encryptedOldPswd = ectr.encryptPassword(ui->edt_oldpswd->text());
	QString encryptedNewPswd = ectr.encryptPassword(ui->edt_newpswd->text());
	m_processor->changePassword( m_userId , encryptedOldPswd , encryptedNewPswd);
}

void JDialogChangePassword::receiveResult(JCode code)
{
	if( 0 == code ){
		QMessageBox::information(
					this,
					tr("change password succees"),
					tr("change password succees"));
		QDialog::accept();
	}else{
		QMessageBox::critical(
					this,
					tr("change password error"),
					tr("change password error : %1").arg(code));
	}
}
