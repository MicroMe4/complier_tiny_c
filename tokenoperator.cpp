#include "tokenoperator.h"
#include <QDebug>

TokenOperator::TokenOperator(const QList<std::tuple<quint32, QString>> lexicalList)
{
    this->toklist = lexicalList;
    this->emptyTuple = std::make_tuple(0xFFFFFFFF,QString());
}

const std::tuple<quint32,QString>& TokenOperator::nextToken(){
    if(this->pointer>=toklist.size()){
        return this->emptyTuple;
    }
    this->pointer += 1;
    //qDebug() << "Token Position:" << this->pointer;
    return toklist.at(pointer);
}

const std::tuple<quint32,QString>& TokenOperator::beforeToken(){
    if(this->pointer <= 0){
        return this->emptyTuple;
    }
    this->pointer -= 1;
    //qDebug() << "Token Position:" << this->pointer;
    return toklist.at(pointer);
}

const std::tuple<quint32,QString>& TokenOperator::NowToken(){
    return toklist.at(pointer);
}

void TokenOperator::resetPointer(){
    this->pointer = -1;
}

 const std::tuple<quint32,QString>& TokenOperator::EmptyToken(){
    return this->emptyTuple;
}

 const quint32& TokenOperator::getTokenCode(){
     return std::get<0>(toklist.at(pointer));
 }

 const QString& TokenOperator::getTokenString(){
     return std::get<1>(toklist.at(pointer));
 }

 bool TokenOperator::atEnd(){
     return this->pointer >= this->toklist.size() - 1;
 }

 const qint32& TokenOperator::getPosition(){
     return this->pointer;
 }
