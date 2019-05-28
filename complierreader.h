#ifndef COMPLIERREADER_H
#define COMPLIERREADER_H
#include <QFile>
#include <QString>

class ComplierReader:public QObject
{
public:
    ComplierReader(const QString& filename);
    ~ComplierReader();
    QStringList getReadContentinList();
    QString getReadContent();
private:
    QFile readFile;
};

#endif // COMPLIERREADER_H
