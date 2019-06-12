#ifndef TOKENOPERATIONER_H
#define TOKENOPERATIONER_H
#include <QList>
#include <QString>
#include <tuple>

class TokenOperationer
{
public:
    TokenOperationer(const QList<std::tuple<quint32,QString>> lexicalList);
    const std::tuple<quint32,QString>& nextToken();
    const std::tuple<quint32,QString>& beforeToken();
    const std::tuple<quint32,QString>& EmptyToken();
    const std::tuple<quint32,QString>& NowToken();
    const quint32& getTokenCode();
    const QString& getTokenString();
    const qint32& getPosition();
    bool atEnd();
    void resetPointer();
private:
    QList<std::tuple<quint32,QString>> toklist;
    std::tuple<quint32,QString> emptyTuple;
    qint32 pointer = -1;
};

#endif // TOKENOPERATIONER_H
