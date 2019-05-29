#ifndef TOKENS_H
#define TOKENS_H

#include <QMap>
#include <QtMath>
#include <QString>

typedef QMap<QString,quint32> Token;

class TokenInstance
{
public:
    TokenInstance();
    bool isKeyword(const QString &s);
    bool isOperatororDelimeter(const QString &s);
    bool isOperatororDelimeter(const QChar &c);
    static bool isRealNumber(const QString &_chk);
    bool isIdentifier(const QString &_chk);
    bool isOperatororDelimeterCombined(const QChar &a,const QChar &b); // 二元运算符的函数
    bool isOperatororDelimeterCombined(const QString &a,const QChar &b); // 二元及以上运算符的函数
    bool isOperatorUseToDivide(const QChar &c);
    static bool isTokenNumberKeywork(const quint32 &kw);
    static bool isTokenNumberOperator(const quint32 &op);
    static bool isTokenNumberIDentifer(const quint32 &id);
    void doAssigntoToken(const QString &strAssign,const quint32 &tk);
    quint32 getCodeofToken(const QString&,const bool &isConstantString=false);
    const static quint32 ConstantNumericCode=0x60000001;
    const static quint32 ConstStrCode=0xB0000001;
    const static quint32 UnknownToken = 0xF0000001;
private:
    Token _Instance;
    const static quint32 EdgeKeywordOperator=34;
    const static quint32 EdgeOperatorRemain=84;
    const static quint32 GeneralizeIdentiferEdge=85;
};

#endif // TOKENS_H
