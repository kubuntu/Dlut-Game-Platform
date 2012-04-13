#include "packagemetainfo.h"

#include <QDomDocument>

#include <QDebug>

const static QString s_osStrList[]={
    "X11",
    "win",
    "error",
};

/*!
    \class PackageMetainfo
    这个类记录的信息必须是人类可读的。
*/

PackageMetainfo::PackageMetainfo()
{
    m_gameId = -1;
    m_name = "noName";
    m_version = "0.0";
    m_os = MAX;
}

void PackageMetainfo::setGameId(int id){
    m_gameId = id;
}

void PackageMetainfo::setName(const QString& str){
    m_name = str;
}

void PackageMetainfo::setVersion(const QString& str){
    m_version = str;
}

void PackageMetainfo::setAuthor(const QString& str){
    m_author = str;
}

void PackageMetainfo::setOrganization(const QString& str){
    m_organization = str;
}

void PackageMetainfo::setIntroduction(const QString& str){
    m_introduction = str;
}

void PackageMetainfo::setOS(OS os){
    m_os = os ;
}

void PackageMetainfo::setOsStr(const QString& str){
    int value = -1 ;
    for(value =0;value<MAX;++value){
        if(s_osStrList[value] == str){
            break;
        }
    }
    if(value >= 0 && value<MAX){
        setOS((OS)value);
    }else{
        setOS(MAX);
    }
}

void PackageMetainfo::setRunFilePath(const QString& str){
    m_runFilePath = str;
}

int PackageMetainfo::gameId()const{
    return m_gameId ;
}

const QString& PackageMetainfo::name()const{
    return m_name;
}

const QString& PackageMetainfo::version()const{
    return m_version ;
}

PackageMetainfo::OS PackageMetainfo::os()const{
    return m_os ;
}

const QString& PackageMetainfo::osStr()const{
    return s_osStrList[m_os];
}

const QString& PackageMetainfo::runFilePath()const{
    return m_runFilePath ;
}

PackageMetainfo PackageMetainfo::fromXML(const QByteArray& data){
    QDomDocument dom;
    dom.setContent(data);
    QDomElement eleInfo = dom.documentElement();
    QDomNodeList nodeList = eleInfo.childNodes();

    PackageMetainfo info;

    for(int i=0;i<nodeList.count();++i){
        QDomNode node = nodeList.at(i);
        qDebug()<<"name : "<<node.nodeName()
                <<" type: "<<node.nodeType()
                <<" text: "<<node.toElement().text();
        if(node.nodeName() == "gameid"){
            info.setGameId(node.toElement().text().toInt());
        }else if(node.nodeName() == "name"){
            info.setName(node.toElement().text());
        }else if(node.nodeName() == "version"){
            info.setVersion(node.toElement().text());
        }else if(node.nodeName() == "author"){
            info.setAuthor(node.toElement().text());
        }else if(node.nodeName() == "organization"){
            info.setOrganization(node.toElement().text());
        }else if(node.nodeName() == "introduction"){
            info.setIntroduction(node.toElement().text());
        }else if(node.nodeName() == "os"){
            info.setOsStr(node.toElement().text());
        }else if(node.nodeName() == "runfilepath"){
            info.setRunFilePath(node.toElement().text());
        }
    }

    return info;
}

QByteArray PackageMetainfo::toXML(const PackageMetainfo& info){
    QDomDocument dom;

    // info
    QDomElement eleInfo = dom.createElement("info");
    dom.appendChild(eleInfo);

    // id
    QDomElement eleGameId = dom.createElement("gameid");
    eleInfo.appendChild(eleGameId);
    QDomText txtGameId = dom.createTextNode(QString::number(info.m_gameId));
    eleGameId.appendChild(txtGameId);

    // name
    QDomElement eleName = dom.createElement("name");
    eleInfo.appendChild(eleName);
    QDomText txtName = dom.createTextNode(info.m_name);
    eleName.appendChild(txtName);

    // version
    QDomElement eleVersion = dom.createElement("version");
    eleInfo.appendChild(eleVersion);
    QDomText txtVersion = dom.createTextNode(info.m_version);
    eleVersion.appendChild(txtVersion);

    // author
    QDomElement eleAuthor = dom.createElement("author");
    eleInfo.appendChild(eleAuthor);
    QDomText txtAuthor = dom.createTextNode(info.m_author);
    eleAuthor.appendChild(txtAuthor);

    // organization
    QDomElement eleOrganization = dom.createElement("organization");
    eleInfo.appendChild(eleOrganization);
    QDomText txtOrganization = dom.createTextNode(info.m_organization);
    eleOrganization.appendChild(txtOrganization);

    // introduction
    QDomElement eleIntroduction = dom.createElement("introduction");
    eleInfo.appendChild(eleIntroduction);
    QDomText txtIntroduction = dom.createTextNode(info.m_introduction);
    eleIntroduction.appendChild(txtIntroduction);

    // os
    QDomElement eleOs = dom.createElement("os");
    eleInfo.appendChild(eleOs);
    QDomText txtOs = dom.createTextNode(info.osStr());
    eleOs.appendChild(txtOs);
    
    // runfilepath
    QDomElement eleRunFilePath = dom.createElement("runfilepath");
    eleInfo.appendChild(eleRunFilePath);
    QDomText txtRunFilePath = dom.createTextNode(info.runFilePath());
    eleRunFilePath.appendChild(txtRunFilePath);

    return dom.toByteArray();
}

PackageMetainfo::OS PackageMetainfo::currentOs(){
#ifdef Q_OS_LINUX
	return PackageMetainfo::X11;
#elif defined Q_OS_WIN32
	return PackageMetainfo::SBMSWIN;
#endif
	return PackageMetainfo::MAX;
}

const QString& PackageMetainfo::currentOsStr(){
	return s_osStrList[ currentOs() ];
}
