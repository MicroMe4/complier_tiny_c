#ifndef TOKENS_H
#define TOKENS_H

#include <map>
#include <QtMath>
#include <QString>

typedef std::map<QString,quint32> Token;

class TokenInstance
{
public:
    TokenInstance();
    bool isKeyword(QString &s);
    bool isOperatororDelimeter(QString &s);
    bool isOperatororDelimeter(QChar &c);
    bool isRealNumber(QString n);
    bool isIdentifier(QString n);
    bool isString(QString str);
    bool isOperatororDelimeterCombined(QChar &a,QChar &b); // 二元运算符的函数
    bool isOperatororDelimeterCombined(QString &a,QChar &b); // 二元及以上运算符的函数
    bool isOperatorUseToDivide(QChar &c);
    quint32 getCodeofToken(QString &c);
    const static quint32 IdentifierCode=84;
    const static quint32 ConstantCode=85;
    const static quint32 TokenNotFind=0xFFFFFFFF;
private:
    Token _Instance;
    const static quint32 EdgeKeywordOperator=34;
    const static quint32 EdgeOperatorRemain=83;
};

#endif // TOKENS_H
