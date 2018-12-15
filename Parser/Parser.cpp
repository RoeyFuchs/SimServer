//
// Created by stav on 12/15/18.
//

#include <algorithm>
#include "Parser.h"


/**
 * ParseVar
 * @param tokens
 * @param symbolTable
 * The function define a new variable and update
 */
void Parser::ParseVar(std::vector<std::string> tokens,std::map<std::string, VarExpression*> &varExpressionTable){
    //check if bind is deifined in line
    if(std::find(tokens.begin(),tokens.end(),"bind")!=tokens.end()){
        //declare new varExpression
        VarExpression* varExp= new VarExpression(tokens[4]);
        //add new Expession to varExpressionTable
        varExpressionTable[tokens[1]]=varExp;
    }
}
/**
 * ParseConnectDataServer
 * @param tokens
 * @return Expression
 * The function parse openDataServer line into an expression
 */
Expression* Parser::ParseConnectDataServer(std::vector<std::string> tokens) {
    Expression *openDataServerExp=new OpenDataServerExpression(std::stoi(tokens[1]), std::stoi(tokens[2]));
    return openDataServerExp;
}
