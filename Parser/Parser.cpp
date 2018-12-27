//
// Created by stav on 12/15/18.
//

#include <algorithm>
#include "Parser.h"
using namespace std;
#define CLOSING_BRACKET "}"
#define PARSE_VAR_BIND_POS 3
#define PARSE_VAR_ARGUMENT_POS 4
#define PARSE_VAR_NAME 1
#define ONE_CHAR 1
#define ONE_CELL 1
#define INITIALIZE_POS 0
#define PARSE_CONNECT_SECOND_ARG 2
#define PRINT_SIZE_LOC 2
#define TWO_CELLS 2
#define EMPTY_SIZE 0

/**
 * ParseVar
 * @param tokens
 * The function define a new variable and update varExpressionTable
 */
shared_ptr<VarExpression> Parser::ParseVarDefined(vector<string> &tokens) {
  this->validateExpression->ValidateVarDefined(tokens);
  shared_ptr<VarExpression> varExp;
  //check if bind is deifined in line
  if (tokens[PARSE_VAR_BIND_POS] == "bind") {
    //check if " is defined
    if (tokens[PARSE_VAR_ARGUMENT_POS][INITIALIZE_POS] == ('\"')) {
      //remove braces
      tokens[PARSE_VAR_ARGUMENT_POS].erase(INITIALIZE_POS, ONE_CHAR);
      tokens[PARSE_VAR_ARGUMENT_POS].erase(tokens[PARSE_VAR_ARGUMENT_POS].size() - ONE_CELL, ONE_CHAR);
      //declare new varExpression
      varExp = make_shared<VarExpression>(tokens[PARSE_VAR_ARGUMENT_POS]);
    } else {
      //make sure second arg is a var
      if (this->expressionMaps->VarExists(tokens[PARSE_VAR_ARGUMENT_POS])) {
        //bind second var path
        varExp = make_shared<VarExpression>(this->expressionMaps->GetExpressionByName(tokens[PARSE_VAR_ARGUMENT_POS])->GetPath());
      } else {
        //undefined var
        throw runtime_error("Error: undefined var");
      }
    }
  } else {
    vector<string> argumentVec = this->utils->Slice(tokens, ONE_CELL, tokens.size() - ONE_CELL);
    if (this->utils->GetPositionsOfExpressions(argumentVec).size() != this->expressionArguments["var"]) {
      throw runtime_error("Error:arguments number at defined var command is not valid");
    }
    vector<string> subVec = this->utils->Slice(tokens, PARSE_VAR_BIND_POS, tokens.size() - ONE_CELL);
    //get expression after '='
    varExp = make_shared<VarExpression>(this->shuntingYard->MakeExpression(subVec));
  }
  return varExp;
}
/**
 * ParseVar
 * @param tokens
 * The function define a new variable and update varExpressionTable
 */
shared_ptr<Expression> Parser::ParseVar(vector<string> &tokens) {
  shared_ptr<VarExpression> varExp;
  varExp = this->ParseVarDefined(tokens);
  //add new Expession to varExpressionTable
  this->expressionMaps->AddExpression(tokens[PARSE_VAR_NAME], varExp);
  return varExp;
}
/**
 * ParseImplementation
 * @param tokens
 * @return Expression
 * The function parse ParseImplementation line into an expression
 */
shared_ptr<Expression> Parser::ParseImplementation(vector<string> &tokens) {
  vector<string>::iterator it = tokens.begin();
  tokens.insert(it, "var");
  shared_ptr<VarExpression> expression = this->ParseVarDefined(tokens);
  shared_ptr<Expression> updateExp;
  shared_ptr<VarExpression> varExpression = this->expressionMaps->GetExpressionByName(tokens[ONE_CELL]);
  if (expression->GetExpression() == nullptr) {
    updateExp = make_shared<UpdateVarExpression>(expression->GetPath(),
                                                 varExpression, (this->connectExpression));
  } else {
    updateExp = make_shared<UpdateVarExpression>(expression,
                                                 varExpression, (this->connectExpression));
  }

  return updateExp;
}
/**
 * ParseOpenDataServer
 * @param tokens
 * @return Expression
 * The function parse openDataServer line into an expression
 */
shared_ptr<Expression> Parser::ParseOpenDataServer(vector<string> &tokens) {
  this->validateExpression->ValidateOpenDataServer(tokens);
  //slice openDataServer word
  vector<string> subVec = this->utils->Slice(tokens, ONE_CELL, tokens.size() - ONE_CELL);
  vector<int> indexesOfArgs = this->utils->GetPositionsOfExpressions(subVec);
  //make sure there is two arguments
  if (indexesOfArgs.size() != this->expressionArguments[tokens[INITIALIZE_POS]]) {
    throw runtime_error("Error:arguments number at openDataServer command is not valid");
  }
  vector<string> firstArg = this->utils->Slice(subVec, indexesOfArgs[INITIALIZE_POS], indexesOfArgs[ONE_CELL] - ONE_CELL);
  vector<string> secondArg = this->utils->Slice(subVec, indexesOfArgs[ONE_CELL], subVec.size() - ONE_CELL);
  shared_ptr<OpenDataServerExpression> openDataServerExp = make_shared<OpenDataServerExpression>(
      this->shuntingYard->MakeExpression(firstArg),
      this->shuntingYard->MakeExpression(secondArg), this->expressionMaps);
  this->openDataServer = openDataServerExp;
  return openDataServerExp;
}
/**
 * ParseConnect
 * @param tokens
 * @param varExpressionTable
 * @return Expression
 * The function parse Connect line into an expression
 */
shared_ptr<Expression> Parser::ParseConnect(vector<string> &tokens) {
  //slice connect and its port
  vector<string> subVec = this->utils->Slice(tokens, PARSE_CONNECT_SECOND_ARG, tokens.size() - ONE_CELL);
  // this->validateExpression->ValidateConnect(subVec);
  shared_ptr<ConnectExpression> connectExp = make_shared<ConnectExpression>(tokens[ONE_CELL],
                                                                            this->shuntingYard->MakeExpression(subVec));
  this->connectExpression = connectExp;
  return connectExp;
}
/**
 * ParsePrint
 * @param tokens
 * @return Expression
 * The function parse print line into an expression
 */
shared_ptr<Expression> Parser::ParsePrint(vector<string> &tokens) {
  this->validateExpression->ValidatePrint(tokens);
  //simple print command, no need to evaluate an expression
  shared_ptr<Expression> printExp;
  if (tokens.size() == this->expressionArguments["print"] + ONE_CELL) {
    if (tokens[ONE_CELL][INITIALIZE_POS] == '\"') {
      tokens[1] = tokens[ONE_CELL].substr(ONE_CHAR, tokens[ONE_CHAR].size() - PRINT_SIZE_LOC);
    }
    //check if print's arg is a string
    if (!this->expressionMaps->VarExists(tokens[ONE_CELL])) {
      //the second arg is string
      printExp = make_shared<PrintExpression>(tokens[ONE_CELL]);
    } else {
      vector<string> subVec = this->utils->Slice(tokens, ONE_CELL, tokens.size() - ONE_CELL);
      printExp = make_shared<PrintExpression>(this->shuntingYard->MakeExpression(subVec));
    }
  }
  return printExp;
}
/**
 * ParseIf
 * @param tokens
 * @return Expression
 * The function parse if line into an expression
 */
shared_ptr<Expression> Parser::ParseIf(vector<string> &tokens) {
  //remove opening bracke if exist
  if (tokens[tokens.size() - ONE_CELL] == "{") {
    tokens = this->utils->Slice(tokens, INITIALIZE_POS, tokens.size() - TWO_CELLS);
  }
  shared_ptr<ConditionParser> ifExp;
  //sub if word
  vector<string> subVec = this->utils->Slice(tokens, ONE_CELL, tokens.size() - ONE_CELL);
  shared_ptr<ConditionExpression> conditionExpression = this->CreateCondition(subVec);
  ifExp = make_shared<IfExpression>(conditionExpression);
  this->PushConditionExpression(ifExp);
  return ifExp;
}
/**
 * ParseWhile
 * @param tokens
 * @return Expression
 * The function parse while line into an expression
 */
shared_ptr<Expression> Parser::ParseWhile(vector<string> &tokens) {
  //remove opening bracket if exist
  if (tokens[tokens.size() - ONE_CELL] == "{") {
    tokens = this->utils->Slice(tokens, INITIALIZE_POS, tokens.size() - TWO_CELLS);
  }
  shared_ptr<ConditionParser> whileExp;
  //sub while word and bracket
  vector<string> subVec = this->utils->Slice(tokens, ONE_CELL, tokens.size() - ONE_CELL);
  shared_ptr<ConditionExpression> conditionExpression = this->CreateCondition(subVec);
  whileExp = make_shared<WhileExpression>(conditionExpression);
  this->PushConditionExpression(whileExp);
  return whileExp;
}
/**
 * CreateCondition
 * @param tokens
 * @return ConditionExpression
 * The function devide string's vector into two expression and get its conditon operator
 */
shared_ptr<ConditionExpression> Parser::CreateCondition(vector<string> &tokens) {
  int operatorIndex = this->utils->GetConditionOperatorPosition(tokens);
  if (operatorIndex == tokens.size() - ONE_CELL || operatorIndex == INITIALIZE_POS) {
    throw runtime_error("Error:arguments number at condition command is not valid");
  }
  vector<string> leftVec = this->utils->Slice(tokens, INITIALIZE_POS, operatorIndex - ONE_CELL);
  vector<string> rightVec = this->utils->Slice(tokens, operatorIndex + ONE_CELL, tokens.size() - ONE_CELL);
  shared_ptr<ConditionExpression> ce = make_shared<ConditionExpression>(tokens[operatorIndex],
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
shared_ptr<Expression> Parser::ParseSleep(vector<string> &tokens) {
  shared_ptr<Expression> sleepExp;
  vector<string> subVec = this->utils->Slice(tokens, ONE_CELL, tokens.size() - ONE_CELL);
  if (this->utils->GetPositionsOfExpressions(subVec).size() != this->expressionArguments[tokens[INITIALIZE_POS]]) {
    throw runtime_error("Error:arguments number at sleep command is not valid");
  }
  sleepExp = make_shared<SleepExpression>(this->shuntingYard->MakeExpression(subVec));
  return sleepExp;
}
/**
 * MakeAnExpression
 * @param tokens
 * @return Expression
 * The function translate tokens into an expression
 */
shared_ptr<Expression> Parser::MakeAnExpression(vector<string> &tokens) {
  shared_ptr<Expression> exp;
  bool hasBracket = false;
  //search for bracket
  if (tokens[0] == "}") {
    //last condition expression is complete
    if (this->currentConditionParse.size() > EMPTY_SIZE) {
      exp = this->currentConditionParse.top();
      this->currentConditionParse.pop();

    } else {
      //bracket error input
      //     throw runtime_error("Error:Bracket input");
    }
  }
  if (tokens[0] == "{") {
    //last condition expression is complete
    if (this->currentConditionParse.size() > EMPTY_SIZE) {
      return nullptr;

    } else {
      //bracket error input
      //   throw runtime_error("Error:Bracket input");
    }
  }
    //search for key words
  else if (tokens[INITIALIZE_POS] == "var") {
    exp = this->ParseVar(tokens);
  } else if (tokens[INITIALIZE_POS] == "sleep") {
    exp = this->ParseSleep(tokens);
  } else if (tokens[INITIALIZE_POS] == "print") {
    exp = this->ParsePrint(tokens);
  } else if (tokens[INITIALIZE_POS] == "openDataServer") {
    exp = this->ParseOpenDataServer(tokens);
  } else if (tokens[INITIALIZE_POS] == "connect") {
    exp = this->ParseConnect(tokens);
  } else if (tokens[INITIALIZE_POS] == "while") {
    exp = this->ParseWhile(tokens);
  } else if (tokens[INITIALIZE_POS] == "if") {
    exp = this->ParseIf(tokens);
  } else if (this->expressionMaps->VarExists(tokens[INITIALIZE_POS]) && tokens[ONE_CELL] == "=") {
    exp = this->ParseImplementation(tokens);
  }
  if (tokens[INITIALIZE_POS] == "var" || tokens[INITIALIZE_POS] == "sleep" || tokens[INITIALIZE_POS] == "print" || tokens[INITIALIZE_POS] == "openDataServer"
      || tokens[INITIALIZE_POS] == "connect") {
    if (this->currentConditionParse.size() > EMPTY_SIZE) {
      this->currentConditionParse.top()->AddExpression(exp);
    }
  }
  return exp;
}
/**
 * ParseSingleLine
 * @param tokens
 * The function executes line
 */
void Parser::ParseSingleLine(vector<string> &tokens) {
  shared_ptr<Expression> exp = this->MakeAnExpression(tokens);
  //privies condition is exist
  if (this->currentConditionParse.size() == EMPTY_SIZE) {
    if (exp != nullptr) {
      //regular command
      exp->Execute();
    }
  }
}
void Parser::ParseLine(vector<string> &tokens) {
  bool isBracket = false;
  if (tokens.size() > ONE_CELL && tokens[tokens.size() - ONE_CELL] == CLOSING_BRACKET) {
    tokens = this->utils->Slice(tokens, INITIALIZE_POS, tokens.size() - TWO_CELLS);
    isBracket = true;
  }
  this->ParseSingleLine(tokens);
  if (isBracket) {
    vector<std::string> bracket = {(std::string) CLOSING_BRACKET};
    this->ParseSingleLine(bracket);
  }

}
void Parser::PushConditionExpression(shared_ptr<ConditionParser> exp) {
  if (this->currentConditionParse.size() != INITIALIZE_POS) {
    //add condition expression to last open condition
    this->currentConditionParse.top()->AddExpression(exp);
  }
  //push it to stack
  this->currentConditionParse.push((exp));
}

