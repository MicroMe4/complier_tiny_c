#include "tokens.h"
#include <QDebug>

TokenInstance::TokenInstance()
{
    // auto.double.int.float.
    this->_Instance["auto"]=0;
    this->_Instance["double"]=1;
    this->_Instance["float"]=2;
    this->_Instance["char"]=3;
    this->_Instance["short"]=4;
    this->_Instance["int"]=5;
    this->_Instance["long"]=6;
    this->_Instance["struct"]=7;
    this->_Instance["register"]=8;
    this->_Instance["void"]=9;
    // dataType based operator type
    this->_Instance["union"]=10;
    this->_Instance["enum"]=11;
    // rename
    this->_Instance["typedef"]=12;
    // readonly
    this->_Instance["const"]=13;
    // to define position
    this->_Instance["extern"]=14;
    // to static in area;
    this->_Instance["static"]=15;
    // loop de loop
    this->_Instance["for"]=16;
    this->_Instance["do"]=17;
    this->_Instance["while"]=18;
    this->_Instance["goto"]=19;
    this->_Instance["continue"]=20;
    this->_Instance["break"]=21;
    // to define data area in different dt
    this->_Instance["unsigned"]=22;
    this->_Instance["signed"]=23;
    // breaches if .. else
    this->_Instance["if"]=24;
    this->_Instance["else"]=25;
    // breach switch case default
    this->_Instance["switch"]=26;
    this->_Instance["case"]=27;
    this->_Instance["default"]=28;
    // can be changed keyword
    this->_Instance["volatile"]=29;
    // else
    this->_Instance["sizeof"]=30;
    this->_Instance["return"]=31;
    this->_Instance["include"]=32;
    this->_Instance["define"]=33;
    // operator +
    this->_Instance["+"]=35;
    this->_Instance["++"]=36;
    this->_Instance["+="]=37;
    // operateor -
    this->_Instance["-"]=38;
    this->_Instance["--"]=39;
    this->_Instance["-="]=40;
    // operator *
    this->_Instance["*"]=41;
    this->_Instance["*="]=42;
    // *2 equ << 2
    this->_Instance["<<"]=43;
    this->_Instance["<<="]=44;
    // operator /
    this->_Instance["/"]=45;
    this->_Instance["/="]=46;
    this->_Instance[">>"]=47;
    this->_Instance[">>="]=48;
    this->_Instance["%"]=49;
    this->_Instance["%="]=50;
    // operator ^
    this->_Instance["^"]=51;
    this->_Instance["^="]=52;
    // logical and bit caculator
    this->_Instance["&"]=53;
    this->_Instance["|"]=54;
    this->_Instance["!"]=55;
    this->_Instance["&="]=56;
    this->_Instance["|="]=57;
    // value assign
    this->_Instance["="]=58;
    // relations
    this->_Instance["&&"]=59;
    this->_Instance["||"]=60;
    // compare
    this->_Instance[">"]=61;
    this->_Instance["<"]=62;
    this->_Instance["=="]=63;
    this->_Instance["!="]=64;
    this->_Instance[">="]=65;
    this->_Instance["<="]=66;
    // dot
    this->_Instance["."]=67;
    // else stuff
    this->_Instance[","]=68;
    this->_Instance["\""]=69;
    this->_Instance["?"]=70;
    this->_Instance[":"]=71;
    this->_Instance[";"]=72;
    this->_Instance["~"]=73;
    this->_Instance["\'"]=74;
    this->_Instance["#"]=75;
    this->_Instance["\\"]=76;
    // pointer
    this->_Instance["->"]=77;
    // postfix ([{}])
    this->_Instance["["]=78;
    this->_Instance["]"]=79;
    this->_Instance["{"]=80;
    this->_Instance["}"]=81;
    this->_Instance["("]=82;
    this->_Instance[")"]=83;
}

bool TokenInstance::isKeyword(const QString &s){
    if(this->_Instance.find(s)!=this->_Instance.end()){
        return this->_Instance.find(s).value() < TokenInstance::EdgeKeywordOperator;
    }
    else return false;
}

bool TokenInstance::isOperatororDelimeter(const QString &s){
    if(this->_Instance.find(s)!=this->_Instance.end()){
        return (!this->isKeyword(s)) && (this->_Instance.find(s).value()<this->EdgeOperatorRemain);
    }
    else return false;
}

bool TokenInstance::isOperatororDelimeter(const QChar &c){
    QString _s(c);
    return this->isOperatororDelimeter(_s);
}

bool TokenInstance::isRealNumber(const QString &_check){
    QString n=_check;
    n=n.remove('\n');
    bool isDotShow=false;
    if(!n[0].isDigit()){
        return false;
    }
    for(QChar c : n){
        if(c=='.'){
            if(!isDotShow){
                isDotShow=true;
            }
            else {
                return false;
            }
        }
        else if(c.isDigit()){
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}

bool TokenInstance::isIdentifier(const QString &_chk){
    QString n = _chk;
    n=n.remove('\n');
    if(n[0].isDigit() || n=="_"){
        return false;
    }
    if(!(this->isKeyword(n))||!(this->isOperatororDelimeter(n))){
        for(QChar c:n){
            if(!(c.isLetterOrNumber()) and !(c == '_')){
                return false;
            }
        }
        return true;
    }
    return true;
}

bool TokenInstance::isOperatororDelimeterCombined(const QChar &a, const QChar &b){
    QString _test;
    _test.append(a).append(b);
    return this->isOperatororDelimeter(_test);
}

bool TokenInstance::isOperatororDelimeterCombined(const QString &a, const QChar &b){
    QString _test;
    _test.append(a).append(b);
    return this->isOperatororDelimeter(_test);
}

bool TokenInstance::isOperatorUseToDivide(const QChar &c){
    if(c==','||c==';'){
        return true;
    }
    return false;
}

bool TokenInstance::isTokenNumberKeywork(const quint32 &kw){
    return kw < TokenInstance::EdgeKeywordOperator;
}

bool TokenInstance::isTokenNumberOperator(const quint32 &op){
    return op > TokenInstance::EdgeKeywordOperator and op < TokenInstance::EdgeOperatorRemain;
}

bool TokenInstance::isTokenNumberIDentifer(const quint32 &id){
    return id == GeneralizeIdentiferEdge;
}

quint32 TokenInstance::getCodeofToken(const QString &c,bool isConstantString ){
    if(this->_Instance.find(c)!=this->_Instance.end()){
        return this->_Instance.find(c).value();
    }
    else if(this->isIdentifier(c)){
        return GeneralizeIdentiferEdge;
    }
    else if(this->isRealNumber(c)){
        return ConstantNumericCode;
    }
    else if(isConstantString){
        return ConstStrCode;
    }
    else return UnknownToken;
}

void TokenInstance::doAssigntoToken(const QString &strAssign,const quint32& tokenID){
    this->_Instance[strAssign]=tokenID;
}
