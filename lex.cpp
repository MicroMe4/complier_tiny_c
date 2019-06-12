#include "lex.h"
#include <QDebug>

Lex::Lex(const QString &p)
{
    this->Inst = nullptr;
    QString preProcessedString;
    for(auto ptr=p.begin();ptr!=p.end();){
        if((*ptr)=='/' and (*(ptr+1)) == '/'){
            ptr+=1;
            while((*ptr)!='\n'){
                ptr++;
            }
        }
        else if((*ptr)=='/' and (*(ptr+1)) == '*'){
            ptr+=2;
            while((*ptr) != '*' and (*(ptr+1)) != '/'){
                ptr++;
            }
            ptr++;
        }
        else {
            preProcessedString.append(*ptr);
            ptr++;
        }
    }
    preProcessedString.remove("\r").remove("\n");
    this->LexQString=preProcessedString;
    //qDebug() << preProcessedString;
}

Lex::Lex(const QStringList &l){
    //QString preProcessingedString;
    QString midProcess,processEnd;
    for (QString s:l) {
        midProcess.append(s);
    }
    for(auto ptr=midProcess.begin();ptr!=midProcess.end();){
        if((*ptr)=='/' and (*(ptr+1)) == '/'){
            ptr+=1;
            while((*ptr)!='\n'){
                ptr++;
            }
        }
        else if((*ptr)=='/' and (*(ptr+1)) == '*'){
            ptr+=2;
            while((*ptr) != '*' and (*(ptr+1)) != '/'){
                ptr++;
            }
            ptr++;
        }
        else {
            processEnd.append(*ptr);
            ptr++;
        }
    }
    this->LexQString=processEnd;
    this->Inst = nullptr;
}

Lex::~Lex(){
    this->Inst = nullptr;
    delete Inst;
}

void Lex::setToken(TokenInstance * newInst){
    this->Inst = newInst;
}

void Lex::analyze(){
    if(this->Inst == nullptr){
        qDebug() << "没有指定Token列表";
    }
    QString midvalue=nullptr;
    qint32 READ_TYPE;
    READ_TYPE=READ_TYPE_NULL;
    bool isReadNumericDot=false; //读小数的时候时候是否读了小数点
    //per process the string
    for (auto c = this->LexQString.begin();c!=this->LexQString.end();){
        //qDebug() << "Middle Value" << midvalue;
        //qDebug() << "c is now" << *c;
        if(c->isDigit()){
            if(READ_TYPE & READ_TYPE_NULL){
                READ_TYPE = READ_TYPE_NUMERIC;
                //qDebug() << "change type of reading to numeric reading";
            }
            else if(READ_TYPE & READ_TYPE_NUMERIC){
                midvalue.append(*c);
                c++;
            }
            else if(READ_TYPE & READ_TYPE_ID){
                READ_TYPE = READ_TYPE_ID;
                midvalue.append(*c);
                c++;
            }
            else if(READ_TYPE & READ_TYPE_OP_DE){
                //this->printLexResultInWord(midvalue);
                this->finalLexial.push_back(std::make_tuple(this->Inst->getCodeofToken(midvalue),midvalue));
                midvalue.clear();
                READ_TYPE=READ_TYPE_NULL;
            }
            else if(READ_TYPE & READ_TYPE_STR){
                midvalue.append(*c);
                c++;
            }
            else if(READ_TYPE & READ_TYPE_ERROR_LEXICAL_IDENTIFER){
                midvalue.append(*c);
                c++;
            }
            else if(READ_TYPE & READ_TYPE_ERROR_LEXICAL_NUMERIC){
                midvalue.append(*c);
                c++;
            }
        }
        else if(c->isLetter()){
            if(READ_TYPE & READ_TYPE_NULL){
                READ_TYPE = READ_TYPE_KWORD | READ_TYPE_ID;
               // qDebug() << "change type of reading to letter reading";
            }
            else if(READ_TYPE & READ_TYPE_ID){
                midvalue.append(*c);
                c++;
            }
            else if(READ_TYPE & READ_TYPE_OP_DE){
                //this->printLexResultInWord(midvalue);
                this->finalLexial.push_back(std::make_tuple(this->Inst->getCodeofToken(midvalue),midvalue));
                midvalue.clear();
                READ_TYPE = READ_TYPE_NULL;
            }
            else if(READ_TYPE & READ_TYPE_NUMERIC){
                READ_TYPE = READ_TYPE_ERROR_LEXICAL_NUMERIC;
                //qDebug() << "change type of reading to " << READ_TYPE;
                midvalue.append(*c);
                c++;
            }
            else if(READ_TYPE & READ_TYPE_STR){
                midvalue.append(*c);
                c++;
            }
            else if(READ_TYPE & READ_TYPE_ERROR_LEXICAL_IDENTIFER){
                midvalue.append(*c);
                c++;
            }
            else if(READ_TYPE & READ_TYPE_ERROR_LEXICAL_NUMERIC){
                midvalue.append(*c);
                READ_TYPE = READ_TYPE_ERROR_LEXICAL_NUMERIC | READ_TYPE_ERROR_LEXICAL_IDENTIFER;
                //qDebug() << "change type of reading to " << READ_TYPE;
                c++;
            }
        }
        else if(this->Inst->isOperatororDelimeter(*c)){
            if(READ_TYPE & READ_TYPE_NULL){
                READ_TYPE=READ_TYPE_OP_DE;
                //qDebug() << "change type of reading to operator reading";
            }
            else if(READ_TYPE & READ_TYPE_NUMERIC){
                READ_TYPE = READ_TYPE_NUMERIC;
                if((*c)=='.' and !isReadNumericDot){
                    midvalue.append(*c);
                    isReadNumericDot=true;
                    c++;
                }
                else{
                    READ_TYPE=READ_TYPE_ERROR_LEXICAL_NUMERIC;
                }
            }
            else if(READ_TYPE & READ_TYPE_ID){
                READ_TYPE = READ_TYPE_ID;
                if((*c)=='_'){
                    midvalue.append(*c);
                    c++;
                }
                else{
                    //this->printLexResultInWord(midvalue);
                    this->finalLexial.push_back(std::make_tuple(this->Inst->getCodeofToken(midvalue),midvalue));
                    midvalue.clear();
                    READ_TYPE = READ_TYPE_NULL;
                }
            }
            else if(READ_TYPE & READ_TYPE_OP_DE){
                if((*c) == '\'' or (*c)=='"'){
                    //this->printLexResultInWord(midvalue);
                    this->finalLexial.push_back(std::make_tuple(this->Inst->getCodeofToken(midvalue),midvalue));
                    midvalue.clear();
                    midvalue.append(*c);
                    //this->printLexResultInWord(midvalue);
                    this->finalLexial.push_back(std::make_tuple(this->Inst->getCodeofToken(midvalue),midvalue));
                    midvalue.clear();
                    //qDebug() << "转换为 STR";
                    READ_TYPE = READ_TYPE_STR;
                    c++;
                }
                else if(this->Inst->isOperatororDelimeterCombined(midvalue,*c)){
                    midvalue.append(*c);
                    c++;
                }
                else{
                    //this->printLexResultInWord(midvalue);
                    this->finalLexial.push_back(std::make_tuple(this->Inst->getCodeofToken(midvalue),midvalue));
                    midvalue.clear();
                    READ_TYPE = READ_TYPE_NULL;
                }
            }
            else if(READ_TYPE & READ_TYPE_STR){
                if((*c)=='\\'){
                    midvalue.append(*c).append(*c+1);
                    c+=2;
                }
                else if(((*c)=='\'') or ((*c)=='\"')){
                   //this->printLexResultInWord(midvalue,true);
                   this->finalLexial.push_back(std::make_tuple(this->Inst->getCodeofToken(midvalue,true),midvalue));
                   midvalue.clear();
                   midvalue.push_back(*c);
                   //this->printLexResultInWord(midvalue);
                   this->finalLexial.push_back(std::make_tuple(this->Inst->getCodeofToken(midvalue),midvalue));
                   midvalue.clear();
                   //qDebug() << "转换为 NULL";
                   READ_TYPE=READ_TYPE_NULL;
                   c++;
                }
            }
            else if(READ_TYPE & READ_TYPE_ERROR_LEXICAL_IDENTIFER){
                if((*c!='_')){
                    //this->printLexResultInWord(midvalue);
                    this->finalLexial.push_back(std::make_tuple(this->Inst->getCodeofToken(midvalue),midvalue));
                    midvalue.clear();
                    READ_TYPE=READ_TYPE_NULL;
                }
                else{
                    midvalue.append(*c);
                    c++;
                }
            }
            else if(READ_TYPE & READ_TYPE_ERROR_LEXICAL_NUMERIC){
                if((*c)=='.'){
                    midvalue.append(*c);
                    c++;
                }
                else {
                    //this->printLexResultInWord(midvalue);
                    this->finalLexial.push_back(std::make_tuple(this->Inst->getCodeofToken(midvalue),midvalue));
                    midvalue.clear();
                    READ_TYPE=READ_TYPE_NULL;
                }
            }

        }
        else if(c->isSpace()){
            if(!(READ_TYPE & READ_TYPE_STR)){
                //this->printLexResultInWord(midvalue);
                this->finalLexial.push_back(std::make_tuple(this->Inst->getCodeofToken(midvalue),midvalue));
                midvalue.clear();
                READ_TYPE = READ_TYPE_NULL;
                //qDebug() << "change type of reading to " << READ_TYPE;
                c++;
            }
            else{
                midvalue.append(*c);
                c++;
            }
        }
        else {
            READ_TYPE=READ_TYPE_ERROR_LEXICAL_IDENTIFER;
            //qDebug() << "change type of reading to " << READ_TYPE;
            midvalue.append(*c);
            c++;
        }
    }
    if(!midvalue.isEmpty()){
        //this->printLexResultInWord(midvalue);
        this->finalLexial.push_back(std::make_tuple(this->Inst->getCodeofToken(midvalue),midvalue));
        midvalue.clear();
    }
    return;
}

QString Lex::getTypeName(const quint32 &TYPE_ID){
    switch (TYPE_ID) {
    case READ_TYPE_ID:
        return "ID";
    case READ_TYPE_KWORD:
        return  "Keyword";
    case READ_TYPE_OP_DE:
        return "Operators";
    case READ_TYPE_NUMERIC:
        return "Number";
    case READ_TYPE_NULL:
        return "Unknown";
    case READ_TYPE_ERROR_LEXICAL_NUMERIC:
        return "Wrong Type A";
    case READ_TYPE_ERROR_LEXICAL_IDENTIFER:
        return "Wrong Type B";
    default:
        return "TYPE Don't Have a Name";
    }
}


void Lex::printLexResultInWord(QString &r,const bool &isConstantString){
    if(isConstantString){
        qDebug() << "<" << r << ", 字符串> 编码:" << this->Inst->getCodeofToken(r,isConstantString) << "\n";
        return;
    }
    if(this->Inst->isKeyword(r)){
        qDebug() << "< " << r << " , 保留字 >  编码：" << this->Inst->getCodeofToken(r) << "\n";
    }
    else if(this->Inst->isOperatororDelimeter(r)){
        qDebug() << "<" << r << ", 分割符或运算符 > 编码：" << this->Inst->getCodeofToken(r) << "\n";
    }
    else if(this->Inst->isRealNumber(r)){
        qDebug() << "< " << r << " , 常量 >  编码：" << this->Inst->getCodeofToken(r) << "\n";
    }
    else if(this->Inst->isIdentifier(r)){
        qDebug() << "<" << r << ", 标识符 > 编码：" << this->Inst->getCodeofToken(r) <<"\n";
    }
    else {
        qDebug() << "<" << r << ", 不在词法分析元素中 > 编码： " << this->Inst->getCodeofToken(r) << "\n";
    }
}

const QList<std::tuple<quint32,QString>>& Lex::getLexList(){
    goThroughToMoveUnneeded();
    return this->finalLexial;
}

void Lex::goThroughToMoveUnneeded(){
    for(auto ptr = this->finalLexial.begin(); ptr!= this->finalLexial.end(); ptr++){
        if(std::get<1>(*ptr) == ""){
            ptr = finalLexial.erase(ptr);
        }
    }
    return;
}
