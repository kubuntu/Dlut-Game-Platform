#include <QCoreApplication>
#include <JArgumentAnalyzer>

#include "jdgpdbsettingcreater.h"

#include <iostream>

void outputUsage(){
	std::cout<<"CreateDbSetting usage : "<<std::endl;
	std::cout<<
"CreateDbSetting --drive=DRIVE --database=DATABASE \
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
	const int necArgc = 2;
	const QString necArgv[necArgc] = {
		QString("drive"),
		QString("database"),
	};
	for(int i=0;i<necArgc;++i){
		if( ! argumentMap.contains(necArgv[i]) ){
			std::cerr<<" missing argument : "
					<<necArgv[i].toStdString()<<std::endl;
			outputUsage() ;
			return 1;
		}
	}
	
	JDgpDbSettingCreater ddsc;
	if( ! ddsc.create( argumentMap ) ){
		std::cerr<<" create setting failed : "
				<<ddsc.errorString().toStdString()<<std::endl;
		return 2;
	}
	
	return 0;
}
