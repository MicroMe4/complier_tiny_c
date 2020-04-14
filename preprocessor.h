#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <QString>

class Preprocessor
{
public:
    Preprocessor();
    ~Preprocessor();
    void Read(const QString& content);
    void RemoveComment();
    void IncludeFiles();
    void ReplaceDefine();
    const QString& GetContent();
    private:
    QString content;
    const static int COMMENT_ONE_LINE_STATUS = -2;
    const static int COMMENT_MULTILINE_STATUS= -3;
    const static int CODE = -1;
};

#endif // PREPROCESSOR_H
