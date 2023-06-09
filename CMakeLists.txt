cmake_minimum_required(VERSION 3.25)
project(boma)

set(CMAKE_CXX_STANDARD 17)

add_executable(boma main.cpp base/Token.cpp base/Token.h base/Lexer.cpp base/Lexer.h base/Location.cpp base/Location.h)
