#include <QCoreApplication>
#include <QtDebug>
#include "complierreader.h"
#include "lex.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ComplierReader b("1.c");
    QString c=b.getReadContent();
    Lex d(c);
    d.analyze();
    return a.exec();
}
