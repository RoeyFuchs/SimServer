#include <iostream>
#include "Expression/Number.h"

using namespace std;

#include "vector"
#include "Expression/MathExpression/Plus.h"
#include "Expression/MathExpression/Minus.h"
#include "Expression/MathExpression/Mult.h"
#include "Expression/MathExpression/Mult.h"
#include "Expression/MathExpression/Div.h"
#include "Tests/UtilsTester.h"
#include "Tests/NumberTest.h"
#include "Tests/ShuntinYardTests.h"
#include "Expression/ShuntingYard.h"
#include <stack>
#include "Client/Client.h"
#include "Tests/ServerTest.h"

int main() {

//UtilsTest();
   //SYTest();
   shared_ptr<Expression> A = make_shared<Number>(5);

   Serv();

   //A->Read();

}