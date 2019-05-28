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
    quint32 getCodeofToken(const QString&,bool isConstantString=false);
    const static quint32 ConstantNumericCode=0x60000001;
    const static quint32 ConstStrCode=0xB0000001;
    const static quint32 UnknownToken = 0xF0000001;
private:
    Token _Instance;
    const static quint32 EdgeKeywordOperator=34;
    const static quint32 EdgeOperatorRemain=84;
    const static quint32 GeneralizeIdentiferEdge=85;
};
/*
 * \begin{tikzpicture}[->,>=stealth',shorten >=1pt,auto,node distance=2.8cm,
                    semithick]
  \tikzstyle{every state}=[fill=yellow1,draw=none,text=black]
 
  \node[state]         (S) at (-6, 0)              {$S$};
  \node[state]         (xin1) at (-2, 3)           {$X^1_{in}$};
  \node[state]         (xin2) at (-2, 1)        {$X^2_{in}$};
  \node[state]         (xin3) at (-2, -1)       {$X^3_{in}$};
  \node[state]         (xin4) at (-2, -3)           {$X^4_{in}$};
  \node[state]         (xout1) at (0, 3)          {$X^1_{out}$};
  \node[state]         (xout2) at (0, 1)        {$X^2_{out}$};
  \node[state]         (xout3) at (0, -1)   {$X^3_{out}$};
  \node[state]         (xout4) at (0, -3)           {$X^4_{out}$};
  \node[state]         (xin5)  at (3, -2)   {$X^5_{in}$};
  \node[state]         (xout5) at (5, -2)   {$X^5_{out}$};
  \node[state]         (DC) at (7, 2)           {$DC$};
 
  \path (S) edge[bend left=26]              node {$\infty$} (xin1)
            edge[bend left=12]              node {$\infty$} (xin2)
            edge[bend right=12]             node {$\infty$} (xin3)
            edge[bend right=26]             node {$\infty$} (xin4)
        (xin1) edge  node {$\alpha=1$} (xout1)
        (xin2) edge  node {$\alpha=1$} (xout2)
        (xin3) edge  node {$\alpha=1$} (xout3)
        (xin4) edge  node {$\alpha=1$} (xout4)
        (xin5) edge  node {$1$} (xout5);
  \draw[->] (xout1) to[out=-30,in=150] node {$\beta$} (xin5);
  \draw[->] (xout2.east) to[out=-15,in=165] node [below] {$\beta$} (xin5);
  \draw[->] (xout3.east) to[out=0,in=180] node [below] {$\beta$} (xin5.west);
  \draw[->] (xout1) to[out=-5,in=175] node {$\infty$} (DC);
  \draw[->] (xout5) to[out=40, in=-120] node {$\infty$} (DC);
\end{tikzpicture}
 
\end{document}
 */

#endif // TOKENS_H
