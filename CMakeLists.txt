cmake_minimum_required(VERSION 3.12)
project(SimServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(SimServer main.cpp Expression/Expression.h Expression/Number.h Expression/BinaryExpression.h Expression/MathExpression/Plus.h Expression/MathExpression/Minus.h
        Expression/MathExpression/Mult.h Expression/MathExpression/Div.h Expression/MathExpression/Modulo.h Expression/UnaryExpression.h
        Expression/MathExpression/Neg.h Tests/NumberTest.h Parser/Parser.cpp Parser/Parser.h Expression/VarExpression.h
        Expression/OpenDataServerExpression.h Expression/ConnectExpression.h Expression/PrintExpression.h Expression/SleepExpression.h
        Expression/ShuntingYard.h Expression/ShuntingYard.cpp Tests/ShuntinYardTests.h Expression/ConditionParser.h Utils/Utils.cpp Utils/Utils.h Expression/ConditionExpression.cpp Expression/ConditionExpression.h Expression/IfExpression.h Expression/WhileExpression.h)