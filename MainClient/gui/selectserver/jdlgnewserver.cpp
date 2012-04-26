#include "jdlgnewserver.h"
#include "ui_jdlgnewserver.h"

#include <QMessageBox>

JDlgNewServer::JDlgNewServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JDlgNewServer)
{
    ui->setupUi(this);
	QRegExpValidator *validator_address = new QRegExpValidator(this);
	validator_address->setRegExp(
		QRegExp(
			"^((\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.){1,3}(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])$"
		)
	);
	ui->edt_address->setValidator(validator_address);
	QIntValidator *validator_port = new QIntValidator(this);
	validator_port->setRange(0,65535);
	ui->edt_port->setValidator(validator_port);
}

JDlgNewServer::~JDlgNewServer()
{
    delete ui;
}

void JDlgNewServer::accept()
{
    if(QHostAddress(ui->edt_address->text()).isNull())
    {
		QMessageBox::critical(this,
							  tr("address is illegal"),
							  tr("the address you input is illegal!"));
        return;
    }
    bool ok;
    int port;
    port=ui->edt_port->text().toInt(&ok);
    if(!ok || port <0 || port >65535 )
    {
		QMessageBox::critical(this,
							 tr("port is illegal"),
							 tr("the port you input is illegal!"));
        return;
    }
    QDialog::accept();
}

SHallServer JDlgNewServer::getServer()const
{
	return SHallServer(QHostAddress(ui->edt_address->text()),ui->edt_port->text().toInt());
}
