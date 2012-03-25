#ifndef JDGPDBTABLECREATER_H
#define JDGPDBTABLECREATER_H

#include <QString>
class JDbConnecter ;

class JDgpDbTableCreater{
public:
	bool create();
	const QString& errorString()const;
private:
	QString m_error ;
};

#endif // JDGPDBTABLECREATER_H

