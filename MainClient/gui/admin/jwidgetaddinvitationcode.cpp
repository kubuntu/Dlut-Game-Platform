#include "jwidgetaddinvitationcode.h"
#include "ui_jwidgetaddinvitationcode.h"

#include <ClientRequest/JUploadInvitationCode>

JWidgetAddInvitationCode::JWidgetAddInvitationCode(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::JWidgetAddInvitationCode)
{
    ui->setupUi(this);
}

JWidgetAddInvitationCode::~JWidgetAddInvitationCode()
{
    delete ui;
}

void JWidgetAddInvitationCode::reset()
{
	ui->edt_code->clear();
}

void JWidgetAddInvitationCode::on_btn_rand_create_clicked()
{
	const int length = 10;
	int i;
	QString code;
	for(i=0;i<length;++i){
		int r = qrand()%36;
		if( r<10){
			code.append(QString::number(r));
		}else{
			code.append(QChar(r-10+'A'));
		}
	}
	ui->edt_code->setText(code);
}

void JWidgetAddInvitationCode::on_btn_send_clicked()
{
	if(ui->edt_code->text().isEmpty()) return ;
	QString code = ui->edt_code->text();

	JUploadInvitationCode uic;
	JCode result = uic.pushInvitationCode(code);
	if( 0 == result ){
		ui->textBrowser->append(
					tr("add code `%1` success")
					.arg(code)
					);
		ui->edt_code->clear();
	}else{
		ui->textBrowser->append(
					tr("add code `%1` failed : %2")
					.arg(code)
					.arg(result)
					);
	}
}
