#include "parser.h"
#include <QDebug>
/* For Parser:
 *  Program -> Main_Type Identifier() block
 *  Main_Type -> Token 0 - 9
 *  Block -> { Stmts }
 *  Decl -> Type Array
 *  Array -> Id [num] | Id [Id] | Id
 *  Stmts -> Stmt Stmts | Stmt
 *  Stmt -> Assign | Decl | while (Bool) | if (Bool) | (Empty)
 */

Parser::Parser(){
    this->tkp = nullptr;
    this->tka = nullptr;
}

Parser::Parser(TokenInstance *in, TokenOperationer *op)
{

    this->tkp = op;
    this->tka = in;
}

void Parser::setTokenInstance(TokenInstance *a){
    this->tka=a;
}

void Parser::syntaxRecursiveDescentAnalysis(){
    while(!tkp->atEnd()){
        _rda_analysis_programa();
    }
}

Parser::~Parser(){
    tkp = nullptr;
    tka = nullptr;
    delete tkp;
    delete tka;
}

void Parser::_rda_analysis_programa(){
    qDebug() << "Token PR";
    tkp->nextToken();
    if(tkp->NowToken() == tkp->EmptyToken()){
        qDebug() << "Error: Analyse:Programa Is Empty. analyzer reached the end of program. The Datatype of program not declared";
    }
    else if(tka->isTokenDataType(tkp->getTokenCode())){
        qDebug() << "Analysis Function (Maybe): Function has a datatype :" << tkp->getTokenString();
    }
    else{
        qDebug() << "Analyse:Programa Is facing an error: the datatype defined by programa is not in list";
    }
    tkp->nextToken();
    if(tkp->NowToken() == tkp->EmptyToken()){
        qDebug() << "Analyse:Programa is empty. analyzer reached the end of program. The Identifier of program not declared";
    }
    else if(tka->isIdentifierToken(tkp->getTokenCode())){
        qDebug() << "Analysis Function (Maybe): Function has a Name :" << tkp->getTokenString();
    }
    else{
        qDebug() << "Analyse:Program encounter error: not Identifier of function";
    }
    tkp->nextToken();
    if(!tka->isLeftParentheses(tkp->getTokenCode())){
        qDebug() << "Found Left Parentheses";
    }
    tkp->nextToken();
    if(!tka->isRightParentheses(tkp->getTokenCode())){
        qDebug() << "Not Found Right Parentheses";
    }
    _rda_analysis_block();
    qDebug() << "Function Analysis Complete";
}

void Parser::_rda_analysis_block(){
    tkp->nextToken();
    if(tka->isTokenBlockBeginOperator(tkp->getTokenCode())){
       _rda_analysis_statements();
       if(tka->isTokenBlockEndOperator(tkp->getTokenCode())){
           return;
       }
    }
    else{
        qDebug() << "Analysis Block Failed.";
    }
}

void Parser::_rda_analysis_statements(){
    if(!tka->isTokenBlockEndOperator(tkp->getTokenCode())){
        _rda_analysis_statement();
        _rda_analysis_statements();
    }
    return;
}

void Parser::_rda_analysis_statement(){
    tkp->nextToken();
    if(tka->isTokenBlockEndOperator(tkp->getTokenCode())){
        return;
    }
    else if(tka->isTokenDataTypeNotVoid(tkp->getTokenCode())){
        tkp->beforeToken();
        _rda_analysis_declare();
    }
    else if(tka->isIdentifierToken(tkp->getTokenCode())){
        //qDebug() << "Identifier!";
        tkp->nextToken();
        if(tka->isLeftParentheses(tkp->getTokenCode())){
            //qDebug() << "Now Doing Function Analyse...";
            // Custom Functions
            tkp->beforeToken();
            tkp->beforeToken();
            _rda_analysis_self_function();
        }
        else if(tka->isAssignValue(tkp->getTokenCode()) or tka->isTokenSelfOperatorAfter(tkp->getTokenCode())){
            // Assign Values
            tkp->beforeToken();
            tkp->beforeToken();
            _rda_analysis_assignvalue();
        }
        else{
            qDebug() << "Fear Nothing Generialized Stuff";
        }
    }
    else if(tka->isIfKeyword(tkp->getTokenCode())){
        tkp->beforeToken();
        _rda_analysis_if();
    }
    else if(tka->isWhileKeyword(tkp->getTokenCode())){
        tkp->beforeToken();
        _rda_analysis_while();
    }
    else if(tka->isReturnKeyword(tkp->getTokenCode())){
        tkp->beforeToken();
        _rda_analysis_return();
    }
    else{
        qDebug() << "Definied No Such Situation." << "Now Token Position at" << tkp->getPosition();
    }
    tkp->nextToken();
    if(tka->isEndStatementToken(tkp->getTokenCode())){
        //qDebug() << "Statement Analyze Complete. No Grammer Mistake Found. Now Token Position is at " << tkp->getPosition();
        return;
    }
    else if(tka->isTokenBlockEndOperator(tkp->getTokenCode())){
        return;
    }
    else{
        qDebug() << "Statement Analyse Failed! We will end the analyse of this statement. Grammer Find Mistakes Between Token No. "<< tkp->getPosition() - 1  << " and "<< tkp->getPosition();
        while(!tka->isEndStatementToken(tkp->getTokenCode())){
            tkp->nextToken();
        }
        qDebug() << "Start another statement check in " << tkp->getPosition();
    }
}

void Parser::_rda_analysis_declare(){
    tkp->nextToken();
    //qDebug() << "Called DECL";
    if(tka->isTokenDataTypeNotVoid(tkp->getTokenCode())){
        _rda_analysis_array();
        return;
    }
    else{
        qDebug() << "Declare, Serious? Not A Declare I found. This Token Is at Position " << tkp->getPosition();
        return;
    }
}

void Parser::_rda_analysis_self_function(){
    //qDebug() << "Called Self - Defined Function";
    tkp->nextToken();
    // qDebug() << "Token Infomation: Code = " << tkp->getTokenCode() << " String =" << tkp->getTokenString();
    if(tka->isIdentifierToken(tkp->getTokenCode())){
        qDebug() << "You called a function named " << tkp->getTokenString();
        tkp->nextToken();
        if(tka->isLeftParentheses(tkp->getTokenCode())){
            tkp->nextToken();
            while(!tka->isRightParentheses(tkp->getTokenCode())){
                tkp->nextToken();
                //qDebug() << "Token Infomation: Code = " << tkp->getTokenCode() << " String =" << tkp->getTokenString();
                if(tka->isConstantNumericToken(tkp->getTokenCode()) or tka->isIdentifierToken(tkp->getTokenCode())){
                    qDebug() << "Parameter: " << tkp->getTokenString();
                    tkp->nextToken();
                    if(tka->isSplitter(tkp->getTokenCode()));
                    else break;
                }
                else if(tka->isQuote(tkp->getTokenCode())){
                    //qDebug() << "Quote Found!";
                    tkp->nextToken();
                    //qDebug() << "Token Infomation: Code = " << tkp->getTokenCode() << " String =" << tkp->getTokenString();
                    if(tka->isConstantStringToken(tkp->getTokenCode())){
                        //qDebug() << "Parameter :" << tkp->getTokenString();
                        tkp->nextToken();
                        if(tka->isQuote(tkp->getTokenCode())){
                            tkp->nextToken();
                            //qDebug() << "Token Infomation: Code = " << tkp->getTokenCode() << " String =" << tkp->getTokenString();
                            if(tka->isSplitter(tkp->getTokenCode()));
                            else break;
                        }
                    }
                }
            }
            if(tka->isRightParentheses(tkp->getTokenCode())){
                qDebug() << "Grammer No Problem";
                return;
            }
            else{
                qDebug() << "Nah. Noy A Self-defined Function that is in Use";
                return;
            }
        }
    }
    else{
        qDebug() << "No Self Defined Function!";
    }
}

void Parser::_rda_analysis_if(){
    tkp->nextToken();
    if(tka->isIfKeyword(tkp->getTokenCode())){
        tkp->nextToken();
        if(tka->isLeftParentheses(tkp->getTokenCode())){
            _rda_analysis_bool_stat();
        }
        tkp->nextToken();
        if(tka->isRightParentheses(tkp->getTokenCode())){
            _rda_analysis_block();
            return;
        }
        else{
            qDebug() << "I don't see a matched right parentheses in token";
        }
    }
}

void Parser::_rda_analysis_bool_stat(){
    // ! a == b // a != b
    tkp->nextToken();
    if(tka->isTokenSelfOperatorBefore(tkp->getTokenCode())){
        tkp->nextToken();
        if(tka->isLeftParentheses(tkp->getTokenCode())){
            _rda_analysis_bool_stat();
            if(tka->isRightParentheses(tkp->getTokenCode())){
                return;
            }
        }
        else{
            qDebug() << "Token List Get A Mistake : Unknown Using of !";
        }
    }
    else if(tka->isLeftParentheses(tkp->getTokenCode())){
        _rda_analysis_bool_stat();
        if(tka->isRightParentheses(tkp->getTokenCode())){
            return;
        }
    }
    else if(tka->isIdentifierToken(tkp->getTokenCode())){
        tkp->nextToken();
        if(tka->isTokenBoolOperator(tkp->getTokenCode())){
            tkp->nextToken();
            if(tka->isIdentifierToken(tkp->getTokenCode()) or tka->isConstantStringToken(tkp->getTokenCode()) or tka->isConstantNumericToken(tkp->getTokenCode())){
                return;
            }
        }
    }
    else if(tka->isConstantStringToken(tkp->getTokenCode())){
        tkp->nextToken();
        if(tka->isTokenBoolOperator(tkp->getTokenCode())){
            tkp->nextToken();
            if(tka->isIdentifierToken(tkp->getTokenCode()) or tka->isConstantStringToken(tkp->getTokenCode())){
                return;
            }
        }
    }
    else if(tka->isConstantNumericToken(tkp->getTokenCode())){
        tkp->nextToken();
        if(tka->isTokenBoolOperator(tkp->getTokenCode())){
            tkp->nextToken();
            if(tka->isIdentifierToken(tkp->getTokenCode()) or tka->isConstantNumericToken(tkp->getTokenCode())){
                return;
            }
        }
    }
    else{
        qDebug() << "I fear there is no symbol says these elements together can treat it as a bool-able statement";
        return;
    }
}

void Parser::_rda_analysis_while(){
    tkp->nextToken();
    if(tka->isWhileKeyword(tkp->getTokenCode())){
        tkp->nextToken();
        if(tka->isLeftParentheses(tkp->getTokenCode())){
            _rda_analysis_bool_stat();
        }
        tkp->nextToken();
        if(tka->isRightParentheses(tkp->getTokenCode())){
            _rda_analysis_block();
            return;
        }
        else{
            qDebug() << "I don't see a matched right parentheses in token";
            return;
        }
    }
}

void Parser::_rda_analysis_assignvalue(){
    tkp->nextToken();
    if(tka->isIdentifierToken(tkp->getTokenCode())){
        tkp->nextToken();
        if(tka->isTokenSelfOperatorAfter(tkp->getTokenCode())){
            return;
        }
        else if(tka->isAssignValue(tkp->getTokenCode())){
            tkp->nextToken();
            if(tka->isConstantNumericToken(tkp->getTokenCode()) or tka->isIdentifierToken(tkp->getTokenCode())){
                tkp->nextToken();
                if(tka->isEndStatementToken(tkp->getTokenCode())){
                    tkp->beforeToken();
                    return;
                }
                else if(tka->isBinaryCaculator(tkp->getTokenCode())){
                    tkp->nextToken();
                    if(tka->isConstantNumericToken(tkp->getTokenCode()) or tka->isIdentifierToken(tkp->getTokenCode())){
                        return;
                    }
                }
            }
        }
    }
    else{
        qDebug() << "It is Not an assignment";
    }
}

void Parser::_rda_analysis_array(){
    tkp->nextToken();
    if(tka->isIdentifierToken(tkp->getTokenCode())){
        tkp->nextToken();
        if(tka->isEndStatementToken(tkp->getTokenCode())){
            tkp->beforeToken();
            return;
        }
        else if(tka->isLeftBracket(tkp->getTokenCode())){
            tkp->nextToken();
            if(tka->isIdentifierToken(tkp->getTokenCode()) or tka->isConstantNumericToken(tkp->getTokenCode())){
                tkp->nextToken();
                if(tka->isRightBracket(tkp->getTokenCode())){
                    return;
                }
            }
        }
    }
    else{
        qDebug() << "Not an Array";
    }
}

void Parser::_rda_analysis_return(){
    tkp->nextToken();
    if(tka->isReturnKeyword(tkp->getTokenCode())){
        tkp->nextToken();
        if(tka->isConstantNumericToken(tkp->getTokenCode()) or tka->isIdentifierToken(tkp->getTokenCode())){
            return;
        }
        else{
            qDebug() << "Return Statement's Variable Wrong.";
        }
    }
    else{
        qDebug() << "Not a return statement";
        return;
    }
}
