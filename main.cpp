#include <QCoreApplication>
#include <QtDebug>
#include "complierreader.h"
#include "lex.h"
#include "tokenoperator.h"
#include "parser.h"

void showHelp(const QString& Appname){
    qDebug() << "Lexical and Parser Solver帮助：";
    qDebug() << Appname << " /AnalysisFilename:yourfilename [/LexOption:[showOption]]";
    qDebug() << "/AnalysisFilename: 后跟读取的文件名称";
    qDebug() << "/Option: 后跟数字：";
    qDebug() << "Show Unknown Token = 1";
    qDebug() << "Show Numeirc = 2";
    qDebug() << "Show Identifer = 4";
    qDebug() << "Show Keyword = 8";
    qDebug() << "Show Operator = 16";
    qDebug() << "Show String and Char = 32";
    qDebug() << "将所需展示的条目的数字加起来放入Option中就是所需输出的条目。";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    quint32 Show = 63;
    QString filename;
    if(a.arguments().size() == 1){
        qDebug() << "参数不足。";
        showHelp(a.arguments().at(0));
        return -1;
    }
    if(a.arguments().size() == 2){
        if(a.arguments().at(1).contains("/AnalysisFilename:")){
            filename = a.arguments().at(1).split(":").at(1);
        }
        else{
            qDebug() << "参数错误。";
            return -2;
        }
    }

    if(a.arguments().size() == 3){
        if(a.arguments().at(1).contains("/AnalysisFilename:")){
            filename = a.arguments().at(1).split(":").at(1);
        }
        else if(a.arguments().at(2).contains("/AnalysisFilename:")){
            filename = a.arguments().at(2).split(":").at(1);
        }
        else{
            qDebug() << "参数错误。";
            return -2;
        }
        if(a.arguments().at(1).contains("/LexOption:")){
            filename = a.arguments().at(1).split(":").at(1);
        }
        else if(a.arguments().at(2).contains("/LexOption:")){
            Show = a.arguments().at(2).split(":").at(1).toUInt();
        }
        else{
            qDebug() << "没有Option参数。继续处理";
        }
    }
    bool isShowUnknown = Show & 0x1;
    bool isShowNumeric = Show & 0x2;
    bool isShowIdentifer = Show & 0x4;
    bool isShowKeyword = Show & 0x8;
    bool isShowOperator = Show & 0x10;
    bool isShowString = Show & 0x20;
    ComplierReader cread(filename);
    TokenInstance tkin;
    Lex d(cread.getReadContent());
    d.setToken(&tkin);
    d.analyze();
    TokenOperator tkop(d.getLexList());
    Parser p(&tkin,&tkop);
    QList<std::tuple<quint32,QString>> tp = d.getLexList();
    for(auto c = tp.begin(); c!= tp.end(); c++){
        if(tkin.isAnyKeyword(std::get<0>(*c)) and isShowKeyword){
            qDebug() << c - tp.begin() << ":Token Code = " << std::get<0>(*c) << " Contents = " << std::get<1>(*c);
        }
        else if(tkin.isAnyOperator(std::get<0>(*c)) and isShowOperator){
            qDebug() << c - tp.begin() << ":Token Code = " << std::get<0>(*c) << " Contents = " << std::get<1>(*c);
        }
        else if(tkin.isIdentifierToken(std::get<0>(*c)) and  isShowIdentifer){
            qDebug() << c - tp.begin() << ":Token Code = " << std::get<0>(*c) << " Contents = " << std::get<1>(*c);
        }
        else if(tkin.isConstantStringToken(std::get<0>(*c)) and isShowString){
            //else if(std::get<0>(*c) == TokenInstance::ConstStrCode and isShowString){
            qDebug() << c - tp.begin() << ":Token Code = " << std::get<0>(*c) << " Contents = " << std::get<1>(*c);
        }
        else if(tkin.isConstantNumericToken(std::get<0>(*c)) and isShowNumeric){
            //else if(std::get<0>(*c) == TokenInstance::ConstantNumericCode and isShowNumeric){
            qDebug() << c - tp.begin() << ":Token Code = " << std::get<0>(*c) << " Contents = " << std::get<1>(*c);
        }
        else if(tkin.isUnknownToken(std::get<0>(*c)) and isShowUnknown){
            //else if(std::get<0>(*c) == TokenInstance::UnknownToken and isShowUnknown){
            qDebug() << c - tp.begin() << ":Token Code = " << std::get<0>(*c) << " Contents = " << std::get<1>(*c);
        }
    }
    p.syntaxRecursiveDescentAnalysis();
    qDebug() << "按Ctrl + C 或者 Ctrl + Z 返回";
    return a.exec();
}
