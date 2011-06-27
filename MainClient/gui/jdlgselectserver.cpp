#include "jdlgselectserver.h"
#include "ui_jdlgselectserver.h"

#include "global/ssubserver.h"

JDlgSelectServer::JDlgSelectServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JDlgSelectServer)
{
    ui->setupUi(this);
}

JDlgSelectServer::~JDlgSelectServer()
{
    delete ui;
}

void JDlgSelectServer::addServer(const SubServer::SSubServer& si)
{
	ui->cb_servers->addItem(tr("%1 %2 %3:%4")
							.arg(si.m_serverId)
							.arg(si.m_name)
							.arg(si.m_address.toString())
							.arg(si.m_port));
}

void JDlgSelectServer::setText(const QString& str)
{
	ui->lab_text->setText(str);
}

JID JDlgSelectServer::getSelectedServer()const
{
	QString select=ui->cb_servers->currentText();
	int index= select.indexOf(tr(" "));
	return select.left(index).toInt();
}
