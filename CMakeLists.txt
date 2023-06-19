cmake_minimum_required(VERSION 3.25)
project(boma)

set(CMAKE_CXX_STANDARD 17)

add_executable(boma main.cpp lexer/Token.cpp lexer/Token.h lexer/Lexer.cpp lexer/Lexer.h lexer/Location.cpp lexer/Location.h parser/Parser.cpp parser/Parser.h)
