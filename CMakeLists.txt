cmake_minimum_required(VERSION 3.12)
project(SimServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(SimServer main.cpp Expression/Expression.h Expression/Number.h Expression/BinaryExpression.h Expression/MathExpression/Plus.h Expression/MathExpression/Minus.h Expression/MathExpression/Mult.h Expression/MathExpression/Div.h Expression/MathExpression/Modulo.h Expression/UnaryExpression.h Expression/MathExpression/Neg.h Tests/NumberTest.h)