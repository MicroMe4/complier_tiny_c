#ifndef LEX_H
#define LEX_H
#include <QString>

#define READ_TYPE_ERROR_LEXICAL_IDENTIFER 1
#define READ_TYPE_ERROR_LEXICAL_NUMERIC 2
#define READ_TYPE_NULL 4
#define READ_TYPE_NUMERIC 8
#define READ_TYPE_ID 16
#define READ_TYPE_KWORD 32
#define READ_TYPE_OP_DE 64

class Lex
{
public:
    Lex(QStringList &p);
    Lex(QString &p);
    void analyze();
private:
    static void printLexResultInWord(QString &r);
    QString LexQString;

};

#endif // LEX_H
