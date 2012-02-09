#include "zipobject.h"

#include <zip.h>
#include <errno.h>

#include <QFileInfo>
#include <QDir>

#include <QDebug>

zipobject::zipobject(const QString& filePath){
    m_filePath = filePath ;
    m_zip = NULL ;
}

zipobject::~zipobject(){
    if(NULL != m_zip){
        close();
    }
}

#define TEST_ZIP \
if( NULL == m_zip){\
    qDebug()<<"zip unopened";\
    return false;\
}

bool zipobject::open(QFlags<OpenModeFlag> flags){
    /*
ZIP_CREATE
    Create the archive if it does not exist.
ZIP_EXCL
    Error if archive already exists.
ZIP_CHECKCONS
    Perform additional consistency checks on the archive, and error if they fail.
     */
    int zipflags = 0 ;
    int errorp = 0;

    if(flags & Create){
        zipflags |= ZIP_CREATE;
    }
    if(flags & ErrorIfExists){
        zipflags |= ZIP_EXCL;
    }
    if(flags & CheckCons){
        zipflags |= ZIP_CHECKCONS;
    }
    m_zip = zip_open(getCharPtr(m_filePath),zipflags,&errorp);
    if(NULL == m_zip){
        qDebug()<<"open failed : "<<errorp;
        char buf[255];
        int nError = zip_error_to_str(buf, sizeof(buf), errorp, errno);
        qDebug()<<nError<<buf;
        return false;
    }
    return true;
}

bool zipobject::addFile(const QString& filePath,const QString& inZipPath){
    TEST_ZIP;
    zip_source* source = zip_source_file(m_zip,getCharPtr(filePath),0,0);
    zip_add(m_zip,getCharPtr(inZipPath),source);
    return true;
}

bool zipobject::writeData(const QByteArray& data,const QString& inZipPath){
    TEST_ZIP;
    int length=data.length();
    void* p=new char[length+1];
    // 此处不得不复制。
    // 由于 libzip 只会在 close 的时候才会真正将数据写入zip文件
    // 如果不复制，写入数据时 data 已经析构，数据内容全部为空
    memcpy(p,data.constData(),length);
    zip_source* pSource = zip_source_buffer(m_zip,p,length,1);
    if(NULL == pSource){
        const char* pStr = zip_strerror(m_zip);
        qDebug()<<"create source failed : "<<pStr;
        return false;
    }else{
        int index = zip_name_locate(m_zip,getCharPtr(inZipPath),0);
        if( -1 == index ){
            int rAdd = zip_add(m_zip,getCharPtr(inZipPath),pSource);
            if( -1 == rAdd ){
                qDebug()<<"add source failed : "<<zip_strerror(m_zip);
            }
            return -1 == rAdd ;
        }else{
            int rReplace = zip_replace(m_zip,index,pSource);
            if( -1 == rReplace ){
                qDebug()<<"replace source failed : "<<zip_strerror(m_zip);
            }
            return -1 == rReplace ;
        }
    }
}

QByteArray zipobject::readData(const QString& inZipPath)const{
    if( NULL == m_zip){
        qDebug()<<"zip unopened";
        return QByteArray();
    }
    int index = zip_name_locate(m_zip,getCharPtr(inZipPath),0);
    if( -1 == index ){
        qDebug()<<"no such file : "<<inZipPath;
        return QByteArray();
    }
    zip_file *pFile = zip_fopen_index(m_zip,index,0);
    if( NULL == pFile){
        qDebug()<<"fopen is NULL"<<zip_strerror(m_zip);
        return QByteArray();
    }
    struct zip_stat stat;
    int rStat = zip_stat_index(m_zip,index, 0, &stat);
    if( -1 == rStat ){
        qDebug()<<"stat failed : "<<zip_strerror(m_zip);
        return QByteArray();
    }
    const int length = stat.size;
    char buffer[length +1 ];
    int rRead = zip_fread(pFile,buffer,sizeof(buffer));
    if( -1 == rRead ){
        qDebug()<<"read failed : "<<zip_strerror(m_zip);
        return QByteArray();
    }
    buffer[rRead]='\0';
    return QByteArray(buffer);
}

bool zipobject::extractTo(const QString& dirPath){
    int num_entries = zip_get_num_files(m_zip) ;
    for( int i = 0 ; i < num_entries ; ++i ){
        qDebug()<<zip_get_name(m_zip,i,0);
        zip_file* pFile = zip_fopen_index(m_zip,i,0);
        struct zip_stat stat ;
        zip_stat_index(m_zip,i,0,&stat);
        
        const int length = stat.size ;
        char buffer[length +1 ] ;
        int rRead = zip_fread(pFile,buffer,sizeof(buffer));
        if( -1 == rRead ){
            qDebug()<<"read failed : "<<zip_strerror(m_zip);
            return false;
        }
        
        QFileInfo fileInfo(dirPath + '/' + stat.name);
        QDir dir = fileInfo.absoluteDir() ;
        if(!dir.mkpath(".")){
            return false;
        }
        
        QFile file(dirPath + '/' + stat.name);
        file.open(QIODevice::WriteOnly);
        file.write(buffer);
        file.close();
    }
    return true;
}

bool zipobject::close(){
    TEST_ZIP;
    int rClose = zip_close(m_zip);
    if( 0 != rClose){
        qDebug()<<"close : "<<rClose<<zip_strerror(m_zip);
    }
    m_zip = NULL ;
    return true;
}

QByteArray zipobject::getCharPtr(const QString& string){
    return string.toLocal8Bit();
}
