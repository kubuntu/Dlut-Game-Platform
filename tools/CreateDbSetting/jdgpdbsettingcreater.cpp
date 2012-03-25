#include "jdgpdbsettingcreater.h"

#include <QSettings>

bool JDgpDbSettingCreater::create(
		const QMap<QString,QString>& argumentMap
	){
	QSettings dgpdbIni ("dgpdb.ini", QSettings::IniFormat);
	
	dgpdbIni.setValue("type","sql");
	
	// drive
	QString drive = argumentMap.value("drive");
	dgpdbIni.setValue("drive",drive);
	
	// database
	QString database = argumentMap.value("database");
	dgpdbIni.setValue(
		QString("%1/database").arg(drive),
		database
	);
	
	// username password hostname
	const static int NUM_KEYS = 3;
	const static QString keys[NUM_KEYS] = {
		"username",
		"password",
		"hostname"
	};
	int i;
	for(i=0;i<NUM_KEYS;++i){
		if(argumentMap.contains(keys[i]) ){
			QString value = argumentMap.value(keys[i]);
			dgpdbIni.setValue(
				QString("%1/%2").arg(drive).arg(keys[i]),
				value
			);
		}
	}
	return true;
}
