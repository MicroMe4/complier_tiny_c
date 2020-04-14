#ifndef LEX_H
#define LEX_H
#include <QString>
#include <QList>
#include "tokens.h"

#define READ_TYPE_ERROR_LEXICAL_IDENTIFER 0x00000001
#define READ_TYPE_ERROR_LEXICAL_NUMERIC 0x00000002
#define READ_TYPE_NULL 0x00000004
#define READ_TYPE_NUMERIC 0x0000008
#define READ_TYPE_ID 0x00000010
#define READ_TYPE_KWORD 0x00000020
#define READ_TYPE_OP_DE 0x00000040
#define READ_TYPE_STR 0x00000080

typedef QList<std::tuple<quint32,QString>> LexList;

class Lex
{
public:
    Lex(const QStringList &p);
    Lex(const QString &p);
    ~Lex();
    void analyze();
    void setToken(TokenInstance *);
    static QString getTypeName(const quint32 &TYPE_ID);
    const QList<std::tuple<quint32,QString>>& getLexList();
    bool operator==(const Lex& a){
        return (this->finalLexial == a.finalLexial) and (this->Inst == a.Inst);
    }
    void goThroughToMoveUnneeded();
private:
    TokenInstance *Inst;
    void printLexResultInWord(QString &r,const bool &isConstantString = false); //for Debug Only
    QString LexQString;
    QList<std::tuple<quint32,QString>> finalLexial;
};

#endif // LEX_H
