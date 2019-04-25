#ifndef COMPLIERREADER_H
#define COMPLIERREADER_H
#include <QFile>
#include <QString>
#include <QIODevice>

class ComplierReader
{
public:
    ComplierReader(std::string filename);
    ~ComplierReader();
    QStringList getReadContentinList();
    QString getReadContent();
private:
    QFile readFile;
};

#endif // COMPLIERREADER_H
