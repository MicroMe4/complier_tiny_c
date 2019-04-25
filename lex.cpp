#include "lex.h"
#include "tokens.h"
#include <QDebug>

Lex::Lex(QString &p)
{
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
    qDebug() << preProcessedString;
}


void Lex::analyze(){
    TokenInstance LexToken;
    QString midvalue=nullptr;
    qint32 READ_TYPE;
    READ_TYPE=READ_TYPE_NULL;
    bool isReadNumericDot=false; //读小数的时候时候是否读了小数点
    //per process the string
    for (auto c = this->LexQString.begin();c!=this->LexQString.end();){
        if(c->isSpace()){
            c++;
            if(midvalue.isEmpty()){
                continue;
            }
            this->printLexResultInWord(midvalue);
            midvalue.clear();
            READ_TYPE=READ_TYPE_NULL;
        }
        else if(c->isDigit()){
            if(READ_TYPE & READ_TYPE_NULL){
                READ_TYPE = READ_TYPE_NUMERIC;
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
                this->printLexResultInWord(midvalue);
                midvalue.clear();
                READ_TYPE=READ_TYPE_NULL;
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
        else if(LexToken.isOperatororDelimeter(*c)){
            if(READ_TYPE & READ_TYPE_NUMERIC){
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
                if((*c)=="_"){
                    midvalue.append(*c);
                    c++;
                }
                else{
                    this->printLexResultInWord(midvalue);
                    midvalue.clear();
                    READ_TYPE = READ_TYPE_NULL;
                }
            }
            else if(READ_TYPE & READ_TYPE_NULL){
                READ_TYPE = READ_TYPE_OP_DE;
            }
            else if(READ_TYPE & READ_TYPE_OP_DE){
                if(LexToken.isOperatororDelimeterCombined(midvalue,*c)){
                    midvalue.append(*c);
                    c++;
                }
                else{
                    this->printLexResultInWord(midvalue);
                    midvalue.clear();
                    READ_TYPE = READ_TYPE_NULL;
                }
            }
            else if(READ_TYPE & READ_TYPE_ERROR_LEXICAL_IDENTIFER){
                this->printLexResultInWord(midvalue);
                midvalue.clear();
                READ_TYPE=READ_TYPE_NULL;
                c++;
            }
            else if(READ_TYPE & READ_TYPE_ERROR_LEXICAL_NUMERIC){
                if((*c)=="."){
                    midvalue.append(*c);
                    c++;
                }
                else {
                    this->printLexResultInWord(midvalue);
                    midvalue.clear();
                    READ_TYPE=READ_TYPE_OP_DE;
                    c++;
                }
            }
        }
        else if(c->isLetter()){
            if(READ_TYPE & READ_TYPE_NULL){
                READ_TYPE = READ_TYPE_KWORD | READ_TYPE_ID;
            }
            else if(READ_TYPE & READ_TYPE_ID){
                midvalue.append(*c);
                c++;
            }
            else if(READ_TYPE & READ_TYPE_OP_DE){
                this->printLexResultInWord(midvalue);
                midvalue.clear();
                READ_TYPE = READ_TYPE_NULL;
            }
            else if(READ_TYPE & READ_TYPE_NUMERIC){
                READ_TYPE = READ_TYPE_ERROR_LEXICAL_NUMERIC;
                midvalue.append(*c);
            }
            else if(READ_TYPE & READ_TYPE_ERROR_LEXICAL_IDENTIFER){
                midvalue.append(*c);
                c++;
            }
            else if(READ_TYPE & READ_TYPE_ERROR_LEXICAL_NUMERIC){
                midvalue.append(*c);
                READ_TYPE = READ_TYPE_ERROR_LEXICAL_NUMERIC | READ_TYPE_ERROR_LEXICAL_IDENTIFER;
                c++;
            }
        }
        else {
            READ_TYPE=READ_TYPE_ERROR_LEXICAL_IDENTIFER;
            midvalue.append(*c);
            c++;
        }
    }
}

void Lex::printLexResultInWord(QString &r){
    TokenInstance c;
    if(c.isKeyword(r)){
        qDebug() << "< " << r << " , 保留字 >  编码：" << c.getCodeofToken(r) << "\n";
    }
    else if(c.isOperatororDelimeter(r)){
        qDebug() << "<" << r << ", 分割符或运算符 > 编码：" << c.getCodeofToken(r) << "\n";
    }
    else if(c.isRealNumber(r)){
        qDebug() << "< " << r << " , 常量 >  编码：" << c.getCodeofToken(r) << "\n";
    }
    else if(c.isIdentifier(r)){
        qDebug() << "<" << r << ", 标识符 > 编码：" << c.getCodeofToken(r) <<"\n";
    }
    else {
        qDebug() << "<" << r << ", 不在词法分析元素中 > 编码： " << c.getCodeofToken(r) << "\n";
    }
}
