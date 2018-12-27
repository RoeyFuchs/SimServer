//
// Created by stav on 12/15/18.
//

#include <algorithm>
#include "Parser.h"
using namespace std;
#define CLOSING_BRACKET "}"

/**
 * ParseVar
 * @param tokens
 * The function define a new variable and update varExpressionTable
 */
shared_ptr<VarExpression> Parser::ParseVarDefined(vector<string> &tokens) {
  this->validateExpression->ValidateVarDefined(tokens);
  shared_ptr<VarExpression> varExp;
  //check if bind is deifined in line
  if (tokens[3] == "bind") {
    //check if " is defined
    if (tokens[4][0] == ('\"')) {
      //remove braces
      tokens[4].erase(0, 1);
      tokens[4].erase(tokens[4].size() - 1, 1);
      //declare new varExpression
      varExp = make_shared<VarExpression>(tokens[4]);
    } else {
      //make sure second arg is a var
      if (this->expressionMaps->VarExists(tokens[4])) {
        //bind second var path
        varExp = make_shared<VarExpression>(this->expressionMaps->GetExpressionByName(tokens[4])->GetPath());
      } else {
        //undefined var
        throw runtime_error("Error: undefined var");
      }
    }
  } else {
    vector<string> argumentVec = this->utils->Slice(tokens, 1, tokens.size() - 1);
    if (this->utils->GetPositionsOfExpressions(argumentVec).size() != this->expressionArguments["var"]) {
      throw runtime_error("Error:arguments number at defined var command is not valid");
    }
    vector<string> subVec = this->utils->Slice(tokens, 3, tokens.size() - 1);
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
  this->expressionMaps->AddExpression(tokens[1], varExp);
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
  shared_ptr<VarExpression> varExpression = this->expressionMaps->GetExpressionByName(tokens[1]);
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
  vector<string> subVec = this->utils->Slice(tokens, 1, tokens.size() - 1);
  vector<int> indexesOfArgs = this->utils->GetPositionsOfExpressions(subVec);
  //make sure there is two arguments
  if (indexesOfArgs.size() != this->expressionArguments[tokens[0]]) {
    throw runtime_error("Error:arguments number at openDataServer command is not valid");
  }
  vector<string> firstArg = this->utils->Slice(subVec, indexesOfArgs[0], indexesOfArgs[1] - 1);
  vector<string> secondArg = this->utils->Slice(subVec, indexesOfArgs[1], subVec.size() - 1);
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
  vector<string> subVec = this->utils->Slice(tokens, 2, tokens.size() - 1);
  // this->validateExpression->ValidateConnect(subVec);
  shared_ptr<ConnectExpression> connectExp = make_shared<ConnectExpression>(tokens[1],
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
  //tokens = this->utils->Slice(tokens, 1, tokens.size() - 1);
  this->validateExpression->ValidatePrint(tokens);
  //simple print command, no need to evaluate an expression
  shared_ptr<Expression> printExp;
  if (tokens.size() == this->expressionArguments["print"] + 1) {
    if (tokens[1][0] == '\"') {
      tokens[1] = tokens[1].substr(1, tokens[1].size() - 2);
    }
    //check if print's arg is a string
    if (!this->expressionMaps->VarExists(tokens[1])) {
      //the second arg is string
      printExp = make_shared<PrintExpression>(tokens[1]);
    } else {
      vector<string> subVec = this->utils->Slice(tokens, 1, tokens.size() - 1);
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
  if (tokens[tokens.size() - 1] == "{") {
    tokens = this->utils->Slice(tokens, 0, tokens.size() - 2);
  }
  shared_ptr<ConditionParser> ifExp;
  //sub if word
  vector<string> subVec = this->utils->Slice(tokens, 1, tokens.size() - 1);
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
  if (tokens[tokens.size() - 1] == "{") {
    tokens = this->utils->Slice(tokens, 0, tokens.size() - 2);
  }
  shared_ptr<ConditionParser> whileExp;
  //sub while word and bracket
  vector<string> subVec = this->utils->Slice(tokens, 1, tokens.size() - 1);
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
  if (operatorIndex == tokens.size() - 1 || operatorIndex == 0) {
    throw runtime_error("Error:arguments number at condition command is not valid");
  }
  vector<string> leftVec = this->utils->Slice(tokens, 0, operatorIndex - 1);
  vector<string> rightVec = this->utils->Slice(tokens, operatorIndex + 1, tokens.size() - 1);
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
  vector<string> subVec = this->utils->Slice(tokens, 1, tokens.size() - 1);
  if (this->utils->GetPositionsOfExpressions(subVec).size() != this->expressionArguments[tokens[0]]) {
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
    if (this->currentConditionParse.size() > 0) {
      exp = this->currentConditionParse.top();
      this->currentConditionParse.pop();

    } else {
      //bracket error input
      //     throw runtime_error("Error:Bracket input");
    }
  }
  if (tokens[0] == "{") {
    //last condition expression is complete
    if (this->currentConditionParse.size() > 0) {
      return nullptr;

    } else {
      //bracket error input
      //   throw runtime_error("Error:Bracket input");
    }
  }
    //search for key words
  else if (tokens[0] == "var") {
    exp = this->ParseVar(tokens);
  } else if (tokens[0] == "sleep") {
    exp = this->ParseSleep(tokens);
  } else if (tokens[0] == "print") {
    exp = this->ParsePrint(tokens);
  } else if (tokens[0] == "openDataServer") {
    exp = this->ParseOpenDataServer(tokens);
  } else if (tokens[0] == "connect") {
    exp = this->ParseConnect(tokens);
  } else if (tokens[0] == "while") {
    exp = this->ParseWhile(tokens);
  } else if (tokens[0] == "if") {
    exp = this->ParseIf(tokens);
  } else if (this->expressionMaps->VarExists(tokens[0]) && tokens[1] == "=") {
    exp = this->ParseImplementation(tokens);
  } else if (tokens[0] != "}" && tokens[0] == "}") {
    throw runtime_error("Error:undefined command");
  }
  if (tokens[0] == "var" || tokens[0] == "sleep" || tokens[0] == "print" || tokens[0] == "openDataServer"
      || tokens[0] == "connect") {
    if (this->currentConditionParse.size() > 0) {
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
  if (this->currentConditionParse.size() == 0) {
    if (exp != nullptr) {
      //regular command
      exp->Execute();
    }
  }
}
void Parser::ParseLine(vector<string> &tokens) {
  bool isBracket = false;
  if (tokens.size() > 1 && tokens[tokens.size() - 1] == CLOSING_BRACKET) {
    tokens = this->utils->Slice(tokens, 0, tokens.size() - 2);
    isBracket = true;
  }
  this->ParseSingleLine(tokens);
  if (isBracket) {
    vector<std::string> bracket = {(std::string) CLOSING_BRACKET};
    this->ParseSingleLine(bracket);
  }

}
void Parser::PushConditionExpression(shared_ptr<ConditionParser> exp) {
  if (this->currentConditionParse.size() != 0) {
    //add condition expression to last open condition
    this->currentConditionParse.top()->AddExpression(exp);
  }
  //push it to stack
  this->currentConditionParse.push((exp));
}

