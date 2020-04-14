#include <iostream>
#include <QCoreApplication>
#include <QtDebug>
#include "preprocessor.h"
#include "complierreader.h"
#include "lex.h"
#include "tokenoperator.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ComplierReader cread("input.txt");
    QFile out("output.txt");
    Preprocessor pre;
    pre.Read(cread.getReadContent());
    TokenInstance tkin;
    Lex d(pre.GetContent());
    d.setToken(&tkin);
    d.analyze();
    auto list = d.getLexList();
    TokenOperator tkop(list);
    QList<std::tuple<quint32,QString>> tp = d.getLexList();
    int key = -1;
    qDebug("请输入 1.去除注释 2.获得标识符 3、获得源代码中的种别");
    std::cin >> key;
    switch (key) {
    case 1:
        out.open(QIODevice::WriteOnly);
        out.write(QByteArray(pre.GetContent().toStdString().c_str()));
        out.write("\n");
        out.close();
        break;
    case 2:
        out.open(QIODevice::WriteOnly);
        for(auto kr = list.begin(); kr!= list.end(); kr++){
            if(tkin.isIdentifierToken(std::get<0>(*kr))){
                out.write(QByteArray(std::get<1>(*kr).toStdString().c_str()));
                out.write("\n");
            }
        }
        out.close();
        break;
    case 3:
        out.open(QIODevice::WriteOnly);
        for(auto kr = list.begin(); kr!= list.end(); kr++){
            QString writer;
            writer.append("<").append(QString::number(std::get<0>(*kr))).append(",").append(std::get<1>(*kr)).append(">").append("\n");
            out.write(QByteArray(writer.toStdString().c_str()));
        }
        out.close();
        break;
    default:
        qDebug() << "wrong input!";
    }
    qDebug() << "按Ctrl + C 或者 Ctrl + Z 返回";
    return a.exec();
}
