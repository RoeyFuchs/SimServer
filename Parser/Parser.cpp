//
// Created by stav on 12/15/18.
//

#include <algorithm>
#include "Parser.h"

/**
 * ParseVar
 * @param tokens
 * The function define a new variable and update varExpressionTable
 */
void Parser::ParseVar(std::vector<std::string> tokens){
    VarExpression* varExp;
    //check if bind is deifined in line
    if(std::find(tokens.begin(),tokens.end(),"bind")!=tokens.end()){
        //declare new varExpression
        varExp= new VarExpression(tokens[4]);
    } else{
        std::vector<std::string> subVec= this->utils->Slice(tokens,3, tokens.size()-1);
        //evaluate expression after '='
        varExp=new VarExpression(this->shuntingYard->MakeExpression(subVec));
    }
    //add new Expession to varExpressionTable
    (*this->varExpressionTable)[tokens[1]]=varExp;
}
/**
 * ParseConnectDataServer
 * @param tokens
 * @return Expression
 * The function parse openDataServer line into an expression
 */
Expression* Parser::ParseOpenDataServer(std::vector<std::string> tokens) {
    vector<string>subVec=this->utils->Slice(tokens,1, tokens.size()-1);
    Expression *openDataServerExp=new OpenDataServerExpression(std::stoi(tokens[1]),
            this->shuntingYard->MakeExpression(subVec)->Execute());
    return openDataServerExp;
}
/**
 * ParseConnect
 * @param tokens
 * @param varExpressionTable
 * @return Expression
 * The function parse Connect line into an expression
 */
Expression* Parser::ParseConnect(std::vector<std::string> tokens) {
    vector<string>subVec=this->utils->Slice(tokens,1, tokens.size()-1);
    Expression* connectExp= new ConnectExpression(tokens[1],
            this->shuntingYard->MakeExpression(subVec)->Execute());
    return connectExp;
}
/**
 * ParsePrint
 * @param tokens
 * @return Expression
 * The function parse print line into an expression
 */
Expression* Parser::ParsePrint(std::vector<std::string> tokens) {
    //simple print command, no need to evaluate an expression
    Expression *printExp;
    if(tokens.size()==2){
        //check if print's arg is a string
        if((*this->varExpressionTable).find(tokens[1])==(*this->varExpressionTable).end()){
            //the second arg is string
            printExp=new PrintExpression(tokens[1]);
        }
    }
    vector<string>subVec=this->utils->Slice(tokens,1, tokens.size()-1);
    printExp=new PrintExpression(this->shuntingYard->MakeExpression(subVec));
    return printExp;
}
/**
 * ParseIf
 * @param tokens
 * @return Expression
 * The function parse if line into an expression
 */
Expression* Parser::ParseIf(std::vector<std::string> tokens) {
    Expression* ifExp;
    //sub if word and bracket
    vector<string>subVec=this->utils->Slice(tokens,1, tokens.size()-2);
    ConditionExpression* conditionExpression= this->CreateCondition(subVec);
    ifExp= new IfExpression(conditionExpression);
    return  ifExp;
}
/**
 * ParseWhile
 * @param tokens
 * @return Expression
 * The function parse while line into an expression
 */
Expression* Parser::ParseWhile(std::vector<std::string> tokens) {
    Expression* whileExp;
    //sub while word and bracket
    vector<string>subVec=this->utils->Slice(tokens,1, tokens.size()-2);
    ConditionExpression* conditionExpression= this->CreateCondition(subVec);
    whileExp = new WhileExpression(conditionExpression);
    return  whileExp;
}
/**
 * CreateCondition
 * @param tokens
 * @return ConditionExpression
 * The function devide string's vector into two expression and get its conditon operator
 */
ConditionExpression* Parser::CreateCondition(std::vector<std::string> tokens) {
    int operatorIndex= this->utils->GetConditionOperatorPosition(tokens);
    vector<string>leftVec=this->utils->Slice(tokens,0, operatorIndex-1);
    vector<string>rightVec=this->utils->Slice(tokens,operatorIndex+1, tokens.size()-1);
    ConditionExpression* ce= new ConditionExpression(tokens[operatorIndex],
                                                     this->shuntingYard->MakeExpression(leftVec),
                                                     this->shuntingYard->MakeExpression(rightVec));
    return ce;
}
/**
 * ParseSleep
 * @param tokens
 * @return  Expression
 * The function parse sleep line into an expression
 */
Expression* Parser::ParseSleep(std::vector<std::string> tokens) {
    Expression* sleepExp;
    vector<string>subVec=this->utils->Slice(tokens,1, tokens.size()-1);
    sleepExp= new SleepExpression(this->shuntingYard->MakeExpression(subVec));
    return sleepExp;
}
/**
 * MakeAnExpression
 * @param tokens
 * @return Expression
 * The function translate tokens into an expression
 */
Expression* Parser::MakeAnExpression(std::vector<std::string> tokens) {
    Expression *exp;
    //search for key words
    if (tokens[0] == "var") {
        this->ParseVar(tokens);
    } else if (tokens[0] == "sleep") {
        exp = this->ParseSleep(tokens);
    } else if (tokens[0] == "print") {
        exp = this->ParsePrint(tokens);
    } else if (tokens[0] == "OpenDataServer") {
        exp = this->ParseOpenDataServer(tokens);
    } else if (tokens[0] == "Connect") {
        exp = this->ParseConnect(tokens);
    } else if (tokens[0]=="while"){
        exp= this->ParseWhile(tokens);
    } else if (tokens[0]=="if"){
        exp= this->ParseIf(tokens);
    } else if(tokens[0]=="}"){
        //last condition expression is complete
        if(this->currentConditionParse!= nullptr){
            //if last expression is a parserCondition type
            if(typeid (this->currentConditionParse->GetLastExp()).name()== typeid(IfExpression).name()||
               typeid (this->currentConditionParse->GetLastExp()).name()== typeid(WhileExpression).name()){
                //TODO maybe downcasting? -> should change its IsComplete member

            }else{
                //The current condition is complete
                this->currentConditionParse->SetIsComplete(true);
            }
        }else{
            //bracket error input
            throw runtime_error("Error:Bracket input");
        }
    }
    return exp;
}
/**
 * ParseLine
 * @param tokens
 * The function executes line
 */
void Parser::ParseLine(std::vector<std::string> tokens) {
   Expression* exp =this->MakeAnExpression(tokens);
    //privies condition is exist
    if(this->currentConditionParse!= nullptr) {
        if(this->currentConditionParse->GetIsComplete()== false) {
            this->currentConditionParse->AddExpression(exp);
        }else {
            this->currentConditionParse->Execute();
            //TODO free memory
        }
    } else{
        //regular command
        exp->Execute();
    }
};
