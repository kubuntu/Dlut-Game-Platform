#include "jdialoguserregister.h"
#include "ui_jdialoguserregister.h"
#include "service/jinputpasswordvalidater.h"

#include <ClientRequest/JRequestUserRegister>

#include <QMessageBox>

JDialogUserRegister::JDialogUserRegister(QWidget *parent) :
    QDialog(parent),
	ui(new Ui::JDialogUserRegister)
{
	m_register = new JRequestUserRegister(this);
    ui->setupUi(this);
}

JDialogUserRegister::~JDialogUserRegister()
{
    delete ui;
}

void JDialogUserRegister::accept()
{
	if(ui->lineEdit_loginname->text().length()<4){
		QMessageBox::critical(this,
							  tr("login name too short"),
							  tr("login name can not be shorter than 4")
							  );
		return;
	}
	if(ui->lineEdit_loginname->text().length()>15){
		QMessageBox::critical(this,
							  tr("login name too long"),
							  tr("login name can not be longer than 15")
							  );
		return;
	}

	JInputPasswordValidater ipv;
	if( ! ipv.validatePassword( ui->lineEdit_password->text() ) ){
		QMessageBox::critical(this,
							  tr("input password error"),
							  ipv.getErrorString());
		return ;
	}

	m_register->sendRegister(ui->lineEdit_loginname->text(),ui->lineEdit_password->text(),ROLE_GAMEPLAYER);
	if(m_register->waitForRegisterResult(1000)){
		QMessageBox::information(this,
								 tr("register succeed"),
								 tr("register succeed")
								 );
		QDialog::accept();
		return ;
	}else{
		QMessageBox::critical(this,
							  tr("register failed"),
							  tr("register failed:%1").arg(m_register->getRegisterError())
							  );
		return ;
	}
}
