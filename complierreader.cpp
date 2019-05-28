#include "complierreader.h"
#include <QDebug>
#include <QException>
ComplierReader::ComplierReader(const QString &filename)
{
    if(this->readFile.isOpen()){
        qDebug() << "Something is wrong here. new Object can read in no way!";
        this->readFile.close();
    }
    this->readFile.setFileName(filename);
    if(this->readFile.exists()){
        this->readFile.open(QIODevice::ReadOnly);
    }
    else{
        qDebug() << "Invalid File";
        throw QException();
    }
}

ComplierReader::ComplierReader(const char* fn){
    if(this->readFile.isOpen()){
        qDebug() << "Something is wrong here. new Object can read in no way!";
        this->readFile.close();
    }
    this->readFile.setFileName(fn);
    if(this->readFile.exists()){
        this->readFile.open(QIODevice::ReadOnly);
    }
    else{
        qDebug() << "Invalid File";
        throw QException();
    }
}

ComplierReader::ComplierReader(const std::string &fn){
    if(this->readFile.isOpen()){
        qDebug() << "Something is wrong here. new Object can read in no way!";
        this->readFile.close();
    }
    this->readFile.setFileName(fn.c_str());
    if(this->readFile.exists()){
        this->readFile.open(QIODevice::ReadOnly);
    }
    else{
        qDebug() << "Invalid File";
        throw QException();
    }
}

ComplierReader::~ComplierReader(){
    if(this->readFile.isOpen()){
        this->readFile.close();
    }
    deleteLater();
}

QStringList ComplierReader::getReadContentinList(){
    QStringList result;
    // flush content to prevent danger
    result.clear();
    QString OneLineContent;
    while(!this->readFile.atEnd()){
        OneLineContent = this->readFile.readLine();
        result.append(OneLineContent);
    }
    readFile.seek(0);
    return result;
}

QString ComplierReader::getReadContent(){
    QString Content;
    while(!this->readFile.atEnd()){
        Content.append(this->readFile.readLine());
    }
    return Content;
}

