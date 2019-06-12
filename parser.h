#ifndef SYNTAX_H
#define SYNTAX_H
#include "lex.h"
#include "tokenoperationer.h"
class Parser
{
public:
    Parser();
    Parser(TokenInstance *a, TokenOperationer *op);
    ~Parser();
    void setTokenInstance(TokenInstance *);
    void syntaxRecursiveDescentAnalysis();
    void setTokenOperator(TokenOperationer *);
private:
    void _rda_analysis_programa();
    void _rda_analysis_block();
    void _rda_analysis_array();
    void _rda_analysis_declare();
    void _rda_analysis_statements();
    void _rda_analysis_statement();
    void _rda_analysis_if();
    void _rda_analysis_while();
    void _rda_analysis_assignvalue();
    void _rda_analysis_bool_stat();
    void _rda_analysis_self_function();
    void _rda_analysis_return();
    TokenInstance *tka;
    TokenOperationer *tkp;
};


#endif // SYNTAX_H
