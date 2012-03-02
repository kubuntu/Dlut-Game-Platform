#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"

#include "jwidgetadmin.h"
#include "jformaddgame.h"
#include "jwidgetaddinvitationcode.h"

#include <Socket/JMainClientSocket>

#include <QMessageBox>

AdminMainWindow::AdminMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminMainWindow)
{
	m_widgetadmin=NULL;
	m_formAddGame = NULL;
	m_widgetAddInvitationCode = NULL;
    ui->setupUi(this);
	connect(JMainClientSocket::getInstance(),
			SIGNAL(disconnected()),
			SLOT(On_socket_disconnected()));
}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
}

void AdminMainWindow::on_actionShow_admin_window_triggered()
{
	if(m_widgetadmin==NULL){
		m_widgetadmin=new JWidgetAdmin(this);
		m_widgetadmin->setWindowFlags(Qt::Window);
	}
	m_widgetadmin->show();
}

void AdminMainWindow::on_actionAdd_game_triggered(){
	if( NULL == m_formAddGame ){
		m_formAddGame = new JFormAddGame(this);
		m_formAddGame->setWindowFlags(Qt::Window);
	}
	m_formAddGame->show();
	m_formAddGame->reset();
}

void AdminMainWindow::on_actionAdd_invitation_code_triggered(){
	if( NULL == m_widgetAddInvitationCode ){
		m_widgetAddInvitationCode = new JWidgetAddInvitationCode(this);
		m_widgetAddInvitationCode->setWindowFlags(Qt::Window);
	}
	m_widgetAddInvitationCode->reset();
	m_widgetAddInvitationCode->show();
}

void AdminMainWindow::On_socket_disconnected()
{
	QMessageBox::critical(this,
						  tr("network disconnected"),
						  tr("network disconnected."));
}
