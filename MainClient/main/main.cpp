#include <QtGui/QApplication>
#include <QFile>

#include <Global/Login>
#include <Socket/JMainClientSocket>
#include <Session/JSession>
#include <Util/JLog>

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
	a.setApplicationName("MainClient");
	loadStyles();
	int rtn ;
	{
		rtn = JDlgSelectServer().exec() ;
		jLog()<<"dlg select server rtn :"<<rtn<<endl;
		if( rtn != QDialog::Accepted ){
			return 0;
		}
	}
	{
		rtn = JDlgLogin().exec() ;
		jLog()<<"dlg login rtn : "<<rtn<<endl;
		if( rtn != QDialog::Accepted ){
			return 0;
		}
	}
	ERole role = JMainClientSocket::getInstance()->getSession()->getRole() ;
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
	rtn = a.exec() ;
	delete win ;
    return rtn;
}
