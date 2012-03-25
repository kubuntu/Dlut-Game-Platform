#ifndef JDGPDBSETTINGCREATER_H
#define JDGPDBSETTINGCREATER_H

#include <QMap>
#include <QString>

class JDgpDbSettingCreater
{
public:
	bool create(
		const QMap<QString,QString>& argumentMap
	);
};

#endif // JDGPDBSETTINGCREATER_H

