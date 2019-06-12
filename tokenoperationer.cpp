#include "tokenoperationer.h"
#include <QDebug>
TokenOperationer::TokenOperationer(const QList<std::tuple<quint32, QString>> lexicalList)
{
    this->toklist = lexicalList;
    this->emptyTuple = std::make_tuple(0xFFFFFFFF,QString());
}

const std::tuple<quint32,QString>& TokenOperationer::nextToken(){
    if(this->pointer>=toklist.size()){
        return this->emptyTuple;
    }
    this->pointer += 1;
    //qDebug() << "Token Position:" << this->pointer;
    return toklist.at(pointer);
}

const std::tuple<quint32,QString>& TokenOperationer::beforeToken(){
    if(this->pointer <= 0){
        return this->emptyTuple;
    }
    this->pointer -= 1;
    //qDebug() << "Token Position:" << this->pointer;
    return toklist.at(pointer);
}

const std::tuple<quint32,QString>& TokenOperationer::NowToken(){
    return toklist.at(pointer);
}

void TokenOperationer::resetPointer(){
    this->pointer -= 1;
}

 const std::tuple<quint32,QString>& TokenOperationer::EmptyToken(){
    return this->emptyTuple;
}

 const quint32& TokenOperationer::getTokenCode(){
     return std::get<0>(toklist.at(pointer));
 }

 const QString& TokenOperationer::getTokenString(){
     return std::get<1>(toklist.at(pointer));
 }

 bool TokenOperationer::atEnd(){
     return this->pointer >= this->toklist.size() - 1;
 }

 const qint32& TokenOperationer::getPosition(){
     return this->pointer;
 }
