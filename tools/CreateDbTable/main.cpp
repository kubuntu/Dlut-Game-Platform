#include <QCoreApplication>
#include "jargumentanalyzer.h"
#include "jdbconnecter.h"
#include "jdgpdbtablecreater.h"

#include <iostream>

void outputUsage(){
	std::cout<<" usage : "<<std::endl;
	std::cout<<" CreateDbTable --drive=DRIVE --database=DATABASE --username=USERNAME --password=PASSWORD"<<std::endl;
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
	
	// --help
	if( aa.hasValue("help") ){
		outputUsage() ;
		return 0;
	}
	
	// necessary argument
	const int necArgc = 4;
	const QString necArgv[necArgc] = {
		QString("drive"),
		QString("database"),
		QString("username"),
		QString("password"),
	};
	for(int i=0;i<necArgc;++i){
		if( ! aa.hasValue(necArgv[i]) ){
			std::cerr<<" missing argument : "
					<<necArgv[i].toStdString()<<std::endl;
			outputUsage() ;
			return 1;
		}
	}
	JDbConnecter dc;
	if( ! dc.connect(
			aa.value("drive"),
			aa.value("database"),
			aa.value("username"),
			aa.value("password")
		)
	){
		std::cerr<<" connect db failed : "
				<<dc.errorString().toStdString()<<std::endl;
		return 2;
	}
	JDgpDbTableCreater dtc;
	if( ! dtc.create() ){
		std::cerr<<dtc.errorString().toStdString()<<std::endl;
		return 3;
	}
	return 0;
}
