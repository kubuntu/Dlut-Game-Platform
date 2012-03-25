#include "jargumentanalyzer.h"

#include <QCoreApplication>

bool JArgumentAnalyzer::analyse(){
	QStringList argv = QCoreApplication::arguments() ;
	argv.pop_front() ;
	return analyseStringList(argv);
}

const QMap<QString,QString>& JArgumentAnalyzer::argumentMap()const{
	return m_values ;
}

const QString& JArgumentAnalyzer::errorString()const{
	return m_error ;
}

bool JArgumentAnalyzer::analyseStringList(const QStringList& sl){
	foreach(QString arg , sl){
		// --xxx=ooo
		QRegExp regkv("--([a-zA-Z]*)=(.*)");
		// --xxx
		QRegExp regk("--([a-zA-Z]*)");
		if( regkv.exactMatch(arg) ){
			QStringList capTxt = regkv.capturedTexts();
			QString key = capTxt.at(1);
			QString value = capTxt.at(2);
			m_values.insert(key,value);
		}else if( regk.exactMatch(arg) ){
			QStringList capTxt = regk.capturedTexts() ;
			QString key = capTxt.at(1);
			m_values.insert(key,QString());
		}else{
			m_error = QString(" error arg : %1 ").arg(arg);
			return false;
		}
	}
	return true;
}
