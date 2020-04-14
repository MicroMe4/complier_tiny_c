#include "preprocessor.h"
#include <iostream>
#include <QStringBuilder>
#define __DEBUG


Preprocessor::Preprocessor(){

}

Preprocessor::~Preprocessor(){
}

void Preprocessor::Read(const QString& content){
    this->content = content;
}


void Preprocessor::RemoveComment(){
    qint64 STATUS = CODE;
    QChar lastfind = 0;
    std::string::iterator bg;
    auto opStr = this->content.toStdString();
    for(auto it = opStr.begin(); it < opStr.end();it++){
        if(STATUS == CODE){
            if(*it == '/'){
                if(*(it+1) == '/'){
                    bg = it;
                    STATUS = COMMENT_ONE_LINE_STATUS;
                }
                else if(*(it+1) == '*'){
                    bg = it;
                    STATUS = COMMENT_MULTILINE_STATUS;
                }
            }
        }
        if(STATUS == COMMENT_MULTILINE_STATUS){
            if(*it == '*'){
                if(*it+1 == '/'){
                    it = opStr.erase(bg, it+2); //it should be it+2; because it erase bg but not erase it+1 till the end; Behavior of GCC version 9.3.0
                    STATUS = CODE;
                }
            }
        }
        if(STATUS == COMMENT_ONE_LINE_STATUS){
            if(!QChar(*it).isSpace()){
                lastfind = *it;
            }
            if(QChar(*it) == '\n'){
                opStr.erase(bg , it); //it should be it; because it erase bg but not erase the current iterator(represent "\n"), the behavior is EXPECTED ; Behavior of GCC version 9.3.0
                if(lastfind == '\\'){
                    bg = it;
                    lastfind = 0;
                    STATUS = COMMENT_ONE_LINE_STATUS;
                }
                else{
                    STATUS = CODE;
                }
            }
        }
    }
    this->content.fromStdString(opStr);
}

void Preprocessor::IncludeFiles(){
    //Include means paste and copy the file. we need to get to location of headers and other thing.
    //such action require huge effort and we will complete include addation here
    return;
}

void Preprocessor::ReplaceDefine(){
    //Include means paste and copy the file. we need to get to location of headers and other thing.
    //such action require huge effort and we will complete include addation here
    return;
}

const QString& Preprocessor::GetContent(){
    return this->content;
}
