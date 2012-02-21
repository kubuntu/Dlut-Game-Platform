#include <QtGui/QApplication>
#include <QFile>

#include <Global/Login>
#include <Socket/JMainClientSocket>
#include <Session/JSession>

#include "gui/gamehall/mainwindow.h"
#include "gui/login/jdlglogin.h"
#include "gui/selectserver/jdlgselectserver.h"
#include "gui/admin/adminmainwindow.h"

void loadStyles(){
	QFile qss("styles/mc.qss");
	qss.open(QFile::ReadOnly);
	qApp->setStyleSheet(qss.readAll());
	qss.close();
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	loadStyles();
	if(JDlgSelectServer().exec() ==QDialog::Rejected){
		return 0;
	}
	if(JDlgLogin().exec()==QDialog::Rejected)
    {
        return 0;
	}
	ERole role = JMainClientSocket::getInstance()->getSession()->getRole() ;
	qDebug()<<"role="<<role ;
	QWidget *win = NULL ;
	switch(role){
	case ROLE_GAMEPLAYER:
	case ROLE_GAMEDESIGNER:
	case ROLE_GAMESERVERRUNNER:
		win = new MainWindow ;
		break;
	case ROLE_ADMIN:
	case ROLE_ROOT:
		win = new AdminMainWindow;
		break;
	}
	if( NULL != win ){
		win->show() ;
	}
	int rtn = a.exec() ;
	delete win ;
    return rtn;
}
