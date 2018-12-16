//
// Created by stav on 12/15/18.
//

#include <algorithm>
#include "Parser.h"


/**
 * ParseVar
 * @param tokens
 * @param symbolTable
 * The function define a new variable and update varExpressionTable
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
Expression* Parser::ParseOpenDataServer(std::vector<std::string> tokens,std::map<std::string, VarExpression*> &varExpressionTable) {
    vector<string> subVec;
    std::copy(tokens.begin()+1, tokens.end(),subVec.begin());
    Expression *openDataServerExp=new OpenDataServerExpression(std::stoi(tokens[1]),
            this->shuntingYard->MakeExpression(subVec,varExpressionTable)->Execute());
    return openDataServerExp;
}
/**
 * ParseConnect
 * @param tokens
 * @param varExpressionTable
 * @return Expression
 * The function parse Connect line into an expression
 */
Expression* Parser::ParseConnect(std::vector<std::string> tokens,std::map<std::string, VarExpression*> &varExpressionTable) {
    vector<string> subVec;
    std::copy(tokens.begin()+1, tokens.end(),subVec.begin());
    Expression* connectExp= new ConnectExpression(tokens[1],
            this->shuntingYard->MakeExpression(subVec,varExpressionTable)->Execute());
    return connectExp;
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
        //check if print's arg is a string
        if(varExpressionTable.find(tokens[1])==varExpressionTable.end()){
            //the second arg is string
            printExp=new PrintExpression(tokens[1]);
        }
    }
    vector<string> subVec;
    std::copy(tokens.begin()+1, tokens.end(),subVec.begin());
    printExp=new PrintExpression(this->shuntingYard->MakeExpression(subVec,varExpressionTable));
    return printExp;
}
/**
 * ParseSleep
 * @param tokens
 * @return  Expression
 * The function parse sleep line into an expression
 */
Expression* Parser::ParseSleep(std::vector<std::string> tokens,std::map<std::string, VarExpression*> &varExpressionTable) {
    Expression* sleepExp;
    vector<string> subVec;
    std::copy(tokens.begin()+1, tokens.end(),subVec.begin());
    sleepExp= new SleepExpression(this->shuntingYard->MakeExpression(subVec,varExpressionTable)->Execute());
    return sleepExp;
}

Expression* Parser::ParseLine(std::vector<std::string> tokens,std::map<std::string, VarExpression*> &varExpressionTable) {
    Expression *currentExp;
    //search for key words
    if (tokens[0] == "var") {
        this->ParseVar(tokens, varExpressionTable);
    } else if (tokens[0] == "sleep") {
        this->ParseSleep(tokens,varExpressionTable);
    } else if (tokens[0] == "print") {
        this->ParsePrint(tokens, varExpressionTable);
    } else if (tokens[0] == "OpenDataServer")
        this->ParseOpenDataServer(tokens, varExpressionTable);
    } else if (tokens[0] == "Connect")
            this->ParseConnect(tokens,varExpressionTable);
    }
}
