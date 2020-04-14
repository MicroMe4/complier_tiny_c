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
    void doAssigntoToken(const QString &strAssign,const quint32 &tk);
    bool isTokenSelfOperatorAfter(const quint32&);
    bool isTokenSelfOperatorBefore(const quint32&);
    bool isTokenBoolOperator(const quint32&);
    bool isTokenBlockBeginOperator(const quint32&);
    bool isTokenBlockEndOperator(const quint32&);
    bool isTokenDataType(const quint32&);
    bool isTokenDataTypeNotVoid(const quint32&);
    bool isEndStatementToken(const quint32&);
    bool isLeftParentheses(const quint32&);
    bool isRightParentheses(const quint32&);
    bool isLeftBracket(const quint32&);
    bool isRightBracket(const quint32&);
    bool isAssignValue(const quint32&);
    bool isForKeyword(const quint32&);
    bool isIfKeyword(const quint32&);
    bool isWhileKeyword(const quint32&);
    bool isSplitter(const quint32&);
    bool isQuote(const quint32&);
    bool isReturnKeyword(const quint32&);
    bool isBinaryCaculator(const quint32&);
    bool isConstantStringToken(const quint32&);
    bool isConstantNumericToken(const quint32&);
    bool isUnknownToken(const quint32&);
    bool isIdentifierToken(const quint32&);
    bool isAnyKeyword(const quint32&);
    bool isAnyOperator(const quint32&);
    quint32 getCodeofToken(const QString&,const bool &isConstantString=false);
private:
    Token _Instance;
    const static quint32 ConstantNumericCode=0x60000001;
    const static quint32 ConstStrCode=0xB0000001;
    const static quint32 UnknownToken = 0xF0000001;
    const static quint32 GeneralizeIdentiferEdge=85;
    const static quint32 EdgeKeywordOperator=34;
    const static quint32 EdgeOperatorRemain=84;
};

#endif // TOKENS_H
