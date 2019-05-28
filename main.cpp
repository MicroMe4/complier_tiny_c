#include <QCoreApplication>
#include <QtDebug>
#include "complierreader.h"
#include "lex.h"
void showHelp(const QString& Appname){
    qDebug() << "Lexical Solver帮助：";
    qDebug() << Appname << " /AnalysisFilename:yourfilename [/Option:[showOption]]";
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
        if(a.arguments().at(1).contains("/Option:")){
            filename = a.arguments().at(1).split(":").at(1);
        }
        else if(a.arguments().at(2).contains("/Option:")){
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
    QList<std::tuple<quint32,QString>> tp = d.getLexList();
    for(auto c = tp.begin(); c!= tp.end(); c++){
        if(TokenInstance::isTokenNumberKeywork(std::get<0>(*c)) and isShowKeyword){
            qDebug() << "Token Code = " << std::get<0>(*c) << " Contents = " << std::get<1>(*c);
        }
        else if(TokenInstance::isTokenNumberOperator(std::get<0>(*c)) and isShowOperator){
            qDebug() << "Token Code = " << std::get<0>(*c) << " Contents = " << std::get<1>(*c);
        }
        else if(TokenInstance::isTokenNumberIDentifer(std::get<0>(*c)) and  isShowIdentifer){
            qDebug() << "Token Code = " << std::get<0>(*c) << " Contents = " << std::get<1>(*c);
        }
        else if(std::get<0>(*c) == TokenInstance::ConstStrCode and isShowString){
            qDebug() << "Token Code = " << std::get<0>(*c) << " Contents = " << std::get<1>(*c);
        }
        else if(std::get<0>(*c) == TokenInstance::ConstantNumericCode and isShowNumeric){
            qDebug() << "Token Code = " << std::get<0>(*c) << " Contents = " << std::get<1>(*c);
        }
        else if(std::get<0>(*c) == TokenInstance::UnknownToken and isShowUnknown){
            qDebug() << "Token Code = " << std::get<0>(*c) << " Contents = " << std::get<1>(*c);
        }
    }
    qDebug() << "在 Linux 下按Ctrl + C 或者 Ctrl + Z 返回";
    return a.exec();
}
