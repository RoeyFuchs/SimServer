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
Expression* Parser::ParseVar(std::vector<std::string> &tokens){
    this->validateExpression->ValidateVarDefined(tokens);
    VarExpression* varExp;
    //check if bind is deifined in line
    if(tokens[3]== "bind"){
        //check if " is defined
        if(tokens[4][0]==('\"')) {
            //remove braces
            tokens[4].erase(0,1);
            tokens[4].erase(tokens[4].size()-1,1);
            //declare new varExpression
            varExp = new VarExpression(tokens[4]);
        } else{
            //make sure second arg is a var
            if(utils->IsVar(tokens[4])){
                //bind second var path
                varExp=new VarExpression((*this->varExpressionTable)[tokens[4]]->GetPath());
            }else{
                //undefined var
                throw runtime_error("Error: undefined var");
            }
        }
    } else{
        vector<std::string> argumentVec=this->utils->Slice(tokens,1, tokens.size()-1);
        if(this->utils->GetPositionsOfExpressions(argumentVec).size()!=this->expressionArguments["var"]){
            throw runtime_error("Error:arguments number at defined var command is not valid");
        }
        std::vector<std::string> subVec= this->utils->Slice(tokens,3, tokens.size()-1);
        //get expression after '='
        varExp=new VarExpression(this->shuntingYard->MakeExpression(subVec));
    }
    //add new Expession to varExpressionTable
    (*this->varExpressionTable)[tokens[1]]=varExp;
    return varExp;
}
/**
 * ParseImplementation
 * @param tokens
 * @return Expression
 * The function parse ParseImplementation line into an expression
 */
Expression* Parser::ParseImplementation(std::vector<std::string> &tokens) {
    std::vector<string>::iterator it=tokens.begin();
    tokens.insert(it,"var");
    return this->ParseVar(tokens);
}
/**
 * ParseOpenDataServer
 * @param tokens
 * @return Expression
 * The function parse openDataServer line into an expression
 */
Expression* Parser::ParseOpenDataServer(std::vector<std::string> &tokens) {
    this->validateExpression->ValidateOpenDataServer(tokens);
    //slice openDataServer word
    vector<string>subVec=this->utils->Slice(tokens,1, tokens.size()-1);
    vector<int> indexesOfArgs=this->utils->GetPositionsOfExpressions(subVec);
    //make sure there is two arguments
    if(indexesOfArgs.size()!=this->expressionArguments[tokens[0]]){
        throw runtime_error("Error:arguments number at openDataServer command is not valid");
    }
    vector<string> firstArg=this->utils->Slice(subVec,indexesOfArgs[0], indexesOfArgs[1]-1);
    vector<string> secondArg=this->utils->Slice(subVec,indexesOfArgs[1], subVec.size()-1);
    Expression *openDataServerExp=new OpenDataServerExpression(
            this->shuntingYard->MakeExpression(firstArg),
            this->shuntingYard->MakeExpression(secondArg));
    return openDataServerExp;
}
/**
 * ParseConnect
 * @param tokens
 * @param varExpressionTable
 * @return Expression
 * The function parse Connect line into an expression
 */
Expression* Parser::ParseConnect(std::vector<std::string> &tokens) {
    //slice connect and its port
    vector<string>subVec=this->utils->Slice(tokens,2, tokens.size()-1);
    this->validateExpression->ValidateConnect(subVec);
    Expression* connectExp= new ConnectExpression(tokens[1],
                                                  this->shuntingYard->MakeExpression(subVec));
    return connectExp;
}
/**
 * ParsePrint
 * @param tokens
 * @return Expression
 * The function parse print line into an expression
 */
Expression* Parser::ParsePrint(std::vector<std::string> &tokens) {
    tokens= this->utils->Slice(tokens,1,tokens.size()-1);
    this->validateExpression->ValidatePrint(tokens);
    //simple print command, no need to evaluate an expression
    Expression *printExp;
    if(tokens.size()==this->expressionArguments["print"]){
        //check if print's arg is a string
        if((*this->varExpressionTable).find(tokens[0])==(*this->varExpressionTable).end()){
            //the second arg is string
            printExp=new PrintExpression(tokens[0]);
        }
    }else{
        printExp=new PrintExpression(this->shuntingYard->MakeExpression(tokens));
    }
    return printExp;
}
/**
 * ParseIf
 * @param tokens
 * @return Expression
 * The function parse if line into an expression
 */
Expression* Parser::ParseIf(std::vector<std::string>& tokens) {
    //remove opening bracke if exist
    if(tokens[tokens.size()-1]=="{"){
        tokens=this->utils->Slice(tokens,0,tokens.size()-2);
    }
    Expression* ifExp;
    //sub if word
    vector<string>subVec=this->utils->Slice(tokens,1, tokens.size()-1);
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
Expression* Parser::ParseWhile(std::vector<std::string>& tokens) {
    //remove opening bracket if exist
    if(tokens[tokens.size()-1]=="{"){
        tokens=this->utils->Slice(tokens,0,tokens.size()-2);
    }
    Expression* whileExp;
    //sub while word and bracket
    vector<string>subVec=this->utils->Slice(tokens,1, tokens.size()-1);
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
ConditionExpression* Parser::CreateCondition(std::vector<std::string>& tokens) {
    int operatorIndex= this->utils->GetConditionOperatorPosition(tokens);
    if(operatorIndex==tokens.size()-1||operatorIndex==0){
        throw runtime_error("Error:arguments number at condition command is not valid");
    }
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
Expression* Parser::ParseSleep(std::vector<std::string> &tokens) {
    Expression* sleepExp;
    vector<string>subVec=this->utils->Slice(tokens,1, tokens.size()-1);
    if(this->utils->GetPositionsOfExpressions(subVec).size()!=this->expressionArguments[tokens[0]])
    {
        throw runtime_error("Error:arguments number at sleep command is not valid");
    }    sleepExp= new SleepExpression(this->shuntingYard->MakeExpression(subVec));
    return sleepExp;
}
/**
 * MakeAnExpression
 * @param tokens
 * @return Expression
 * The function translate tokens into an expression
 */
Expression* Parser::MakeAnExpression(std::vector<std::string>& tokens) {
    Expression *exp;
    bool hasBracket= false;
    //search for bracket
    if(tokens[0]=="}"||tokens[tokens.size()-1]=="}") {
        hasBracket= true;
        tokens= this->utils->Slice(tokens,0,tokens.size()-2);
    }
    //search for key words
    if (tokens[0] == "var") {
        exp=this->ParseVar(tokens);
    } else if (tokens[0] == "sleep") {
        exp = this->ParseSleep(tokens);
    } else if (tokens[0] == "print") {
        exp = this->ParsePrint(tokens);
    } else if (tokens[0] == "openDataServer") {
        exp = this->ParseOpenDataServer(tokens);
    } else if (tokens[0] == "connect") {
        exp = this->ParseConnect(tokens);
    } else if (tokens[0]=="while"){
        exp= this->ParseWhile(tokens);
    } else if (tokens[0]=="if"){
        exp= this->ParseIf(tokens);
    } else if (this->utils->IsVar(tokens[0])&&tokens[1]=="="){
        exp= this->ParseImplementation(tokens);
    }else{
        throw runtime_error("Error:undefined command");
    }
    if(hasBracket){
        //last condition expression is complete
        if(this->currentConditionParse!= nullptr){
            //if last expression is a parserCondition type
            if(typeid (this->currentConditionParse->GetLastExp()).name()== typeid(IfExpression).name()||
               typeid (this->currentConditionParse->GetLastExp()).name()== typeid(WhileExpression).name()){
                ConditionParser* conditionParser=(ConditionParser*)this->currentConditionParse->GetLastExp();
                conditionParser->SetIsComplete(true);

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
void Parser::ParseLine(std::vector<std::string> &tokens) {
    Expression* exp =this->MakeAnExpression(tokens);
    //privies condition is exist
    if(this->currentConditionParse!= nullptr) {
        if(this->currentConditionParse->GetIsComplete()== false) {
            this->currentConditionParse->AddExpression(exp);
        }else {
            this->currentConditionParse->Execute();
        }
    } else{
        //check if current exp is a condition
        if(typeid (*exp).name()== typeid(IfExpression).name()||
           typeid (*exp).name()== typeid(WhileExpression).name()) {
            this->currentConditionParse= (ConditionParser*)exp;
        }else{
            //regular command
            exp->Execute();
        }
    }
};
