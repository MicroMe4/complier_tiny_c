#ifndef COMPLIERREADER_H
#define COMPLIERREADER_H
#include <QFile>
#include <QString>

class ComplierReader:public QObject
{
public:
    ComplierReader(const QString& filename);
    ComplierReader(const char* filename);
    ComplierReader(const std::string& filename);
    ~ComplierReader();
    QStringList getReadContentinList();
    QString getReadContent();
private:
    QFile readFile;
};

#endif // COMPLIERREADER_H
