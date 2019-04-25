#include "complierreader.h"
#include <QDebug>

ComplierReader::ComplierReader(std::string filename)
{
    if(this->readFile.isOpen()){
        qDebug() << "Something is wrong here. new Object can read in no way!";
        this->readFile.close();
    }
    this->readFile.setFileName(QString(filename.c_str()));
    this->readFile.open(QIODevice::ReadOnly);
}

ComplierReader::~ComplierReader(){
    this->readFile.close();
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

