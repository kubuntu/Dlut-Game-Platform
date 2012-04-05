#ifndef JDGPDBTABLECREATER_H
#define JDGPDBTABLECREATER_H

#include <QString>

class JDgpDbTableCreater{
public:
	bool create();
	const QString& errorString()const;
private:
	QString m_error ;
};

#endif // JDGPDBTABLECREATER_H

