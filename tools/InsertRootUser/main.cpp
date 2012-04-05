#include <QCoreApplication>
#include <JArgumentAnalyzer>
#include <JDbConnecter>

#include "jrootuserinserter.h"

#include <iostream>

void outputUsage(){
	std::cout<<"InsertRootUser usage : "<<std::endl;
	std::cout<<
"InsertRootUser --drive=DRIVE --database=DATABASE --rootpassword=ROOTPASSWORD \
	[--username=USERNAME] \
	[--password=PASSWORD] \
	[--hostname=HOSTNAME]"
			<<std::endl;
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	
	// analyse argument list
	JArgumentAnalyzer aa;
	if( ! aa.analyse()){
		std::cerr<<aa.errorString().toStdString()<<std::endl;
		return 1;
	}
	const QMap<QString,QString>& argumentMap = aa.argumentMap() ;
	
	// --help
	if( argumentMap.contains("help") ){
		outputUsage() ;
		return 0;
	}
	
	// necessary argument
	const int necArgc = 3;
	const QString necArgv[necArgc] = {
		QString("drive"),
		QString("database"),
		QString("rootpassword"),
	};
	for(int i=0;i<necArgc;++i){
		if( ! argumentMap.contains(necArgv[i]) ){
			std::cerr<<" missing argument : "
					<<necArgv[i].toStdString()<<std::endl;
			outputUsage() ;
			return 1;
		}
	}
	
	JDbConnecter dc;
	if( ! dc.connect( argumentMap ) ){
		std::cerr<<" connect db failed : "
				<<dc.errorString().toStdString()<<std::endl;
		return 2;
	}
	
	JRootUserInserter rui;
	if( ! rui.insert( argumentMap.value("rootpassword" ) ) ){
		std::cerr<<rui.errorString().toStdString()<<std::endl;
		return 3;
	}
	return 0;
}
