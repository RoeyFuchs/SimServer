cmake_minimum_required(VERSION 3.12)
project(SimServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(SimServer main.cpp Expression/Expression.h Expression/Number.h Expression/BinaryExpression.h Expression/Plus.h Expression/Minus.h Expression/Mult.h Expression/Div.h Expression/Modulo.h Expression/UnaryExpression.h Expression/Neg.h)