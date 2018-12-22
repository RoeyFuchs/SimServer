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
#include "Tests/ParserTests.h"
#include "Tests/NumberTest.h"
#include "Tests/ShuntinYardTests.h"
#include "Expression/ShuntingYard.h"
#include <stack>
#include "Utils/Utils.h"

int main() {
    //unordered_map<int, string> a = Utils::GetXmlOrder();
    //cout<< "ds" <<endl;

   //RunParserTests();
   //SYTest();
   auto A = make_shared<ExpressionMaps>();
   auto B = make_shared<OpenDataServerExpression>(make_shared<Number>(5400),make_shared<Number>(5),A);
   B->Execute();



}