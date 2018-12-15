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
/**
 * ParsePrint
 * @param tokens
 * @param varExpressionTable
 * @return Expression
 * The function parse print line into an expression
 */
Expression* Parser::ParsePrint(std::vector<std::string> tokens,std::map<std::string, VarExpression*> &varExpressionTable) {
    //simple print command, no need to evaluate an expression
    Expression *printExp;
    if(tokens.size()==2){
        //check if print's arg is a var
        if(varExpressionTable.find(tokens[1])!=varExpressionTable.end()){
            printExp=new PrintExpression(varExpressionTable[tokens[1]]);
        } else{
            //the second arg is string
            printExp=new PrintExpression(tokens[1]);
        }
    }else{
        //complicate axpression-> shunting yard is needed for evaluation
        //TODO evaluate the expression
    }
    return printExp;
}
Expression* Parser::ParseSleep(std::vector<std::string> tokens) {
    Expression* sleepExp;
    try {
        double sleepingTime= stoi(tokens[1]);
        sleepExp=new SleepExpression(sleepingTime);
    }catch (exception e){
        //sleeping time is not a number
        throw new runtime_error("Error: Sleeping time must be a number");
    }

}
