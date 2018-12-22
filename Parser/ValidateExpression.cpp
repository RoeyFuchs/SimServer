//
// Created by stav on 12/20/18.
//

#include "ValidateExpression.h"
#include <stdexcept>
#include <algorithm>
#define BIND_LEN 5
#define VAR_WITHOUT_BIND 4
#define BIND_POS 3
#define BIND_EQUALS_POS 2
#define OPEN_DATA_SERVER_LEN 3
/**
 * ValidateExpression
 * @param tokens
 * The function checks for leagl arguments number
 */
void ValidateExpression::ValidateVarDefined(vector<string> &tokens) {
    if(tokens[BIND_EQUALS_POS]!="="){
        throw runtime_error ("Error: undefined var");
    }
    //var x= bind ...
    if(tokens[BIND_POS]== "bind") {
        //make sure there is enough arguments
        if (tokens.size() < BIND_LEN) {
            throw runtime_error("Error:Not enough arguments at defined var command");
        }
    } else{
        //var x =..
        if(tokens.size()<VAR_WITHOUT_BIND){
            throw runtime_error("Error:Not enough arguments at defined var command");
        }
    }
}
/**
 * ValidateOpenDataServer
 * @param tokens
 * The function checks for leagl arguments number
 */
void ValidateExpression::ValidateOpenDataServer(vector<string> &tokens) {
    //make sure there is enough arguments
    if (tokens.size() < OPEN_DATA_SERVER_LEN) {
        throw runtime_error("Error:Not enough arguments at OpenDataServer command");
    }
}
/**
 * ValidateOpenDataServer
 * @param tokens
 * The function checks for leagl arguments number
 */
void ValidateExpression::ValidateConnect(vector<string> &tokens) {
    //make sure there is enough arguments
    if (tokens.size() < this->expressionArguments["connect"]) {
        throw runtime_error("Error:arguments number at connect command is not valid");
    }
}
/**
 * ValidatePrint
 * @param tokens
 * The function checks for leagl arguments number
 */
void ValidateExpression::ValidatePrint(vector<string> &tokens) {
    //make sure there is enough arguments
    if (tokens.size() < this->expressionArguments["print"]) {
        throw runtime_error("Error:arguments number at print command is not valid");
    }
}