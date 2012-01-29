#include "packagemetainfo.h"

#include <QDomDocument>

#include <QDebug>

/*!
    \class PackageMetainfo
    这个类记录的信息必须是人类可读的。
*/

PackageMetainfo::PackageMetainfo()
{
    m_gameId = -1;
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

    return dom.toByteArray();
}
