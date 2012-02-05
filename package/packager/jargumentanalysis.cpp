#include "jargumentanalysis.h"

#include <QCoreApplication>
#include <QStringList>

JArgumentAnalysis* JArgumentAnalysis::s_instance = NULL ;

JArgumentAnalysis* JArgumentAnalysis::getInstance(){
    if( NULL == s_instance ){
        s_instance = new JArgumentAnalysis
                (QCoreApplication::instance());
        s_instance->analysis();
    }
    return s_instance;
}

const QString& JArgumentAnalysis::path()const{
    return m_path ;
}

const QList<QRegExp>& JArgumentAnalysis::ignoreList()const{
    return m_ignoreList ;
}

bool JArgumentAnalysis::isEscapeDgppkg()const{
    return true;
}

JArgumentAnalysis::JArgumentAnalysis(QObject *parent) :
    QObject(parent)
{
    m_path = ".";
}

void JArgumentAnalysis::analysis(){
    QStringList arguments = QCoreApplication::arguments();
    QStringList::const_iterator it = arguments.constBegin();
    for(++it;it!=arguments.constEnd();++it){
        if(*it == "-i"){
            ++it ;
            m_ignoreList.push_back(QRegExp(*it));
        }else{
            m_path = *it;
        }
    }
}
