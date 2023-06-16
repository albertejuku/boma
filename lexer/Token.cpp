//
// Created by albert on 6/8/23.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <iomanip>
#include "Token.h"


string tokenList[] = {
        // Single-character tokens
        "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE", "LEFT_SQUARE_BRACKET", "RIGHT_SQUARE_BRACKET",
        "NOT", "SINGLE_QUOTE", "DOUBLE_QUOTE", "BACKTICK",
        "COMMA", "SEMICOLON", "COLON",

        "ARROW",

        // Arithmetic operators
        "ADD", "SUB", "MULT", "DIV", "MOD", "INC", "DEC",
        "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "MULT_ASSIGN", "MOD_ASSIGN", "DIV_ASSIGN",
        "EQUALS", "NOT_EQUALS", "GREATER_THAN", "LESS_THAN", "GREATER_THAN_EQUAL", "LESS_THAN_EQUAL",
        "AND", "OR", "BIT_AND", "BIT_OR", "BIT_NOT", "XOR", "LEFT_SHIFT", "RIGHT_SHIFT",
        "TERNARY", "DOT", "BOMA_NULL", "NULL_COALISING",

        // Literals
        "IDENTIFIER", "CHAR", "STRING", "FLOAT", "INT", "BYTE", "BOOLEAN", "TRUE", "FALSE", "HEX", "OCTAL", "BINARY", "INT_LITERAL", "FLOAT_LITERAL", "STRING_LITERAL", "CHAR_LITERAL", "BYTE_LITERAL",
        "LIST", "ARRAY", "SET", "MAP", "OBJECT", "JSON",
        "CLASS", "INTERFACE",

        // Keywords
        "VAR", "RETURN", "CONST",
        "VOID", "PRINT", "INPUT",
        "ENUM", "CONTINUE", "BREAK",

        // Control flow
        "IF", "ELSE", "ELSE_IF", "WHILE", "DO", "FOR", "SWITCH", "CASE", "FOR_EACH",
        "THROW", "TRY", "CATCH", "FINALLY",


        "NAL",
        // End-of-file
        "END_OF_INPUT"
};


Token* createToken(TokenCode code, const string& lexeme, int line, int column) {
    auto* token = new Token();
    token->code = code;
    token->lexeme = lexeme;
    token->location = *createLocation(line, column);
    return token;
}


void print(const Token& token) {
    std::cout << std::left << std::setw(20) << tokenList[token.code]
              << std::setw(15) << token.lexeme
              << token.location.line << ":" << token.location.column << std::endl;
}

void freeToken(Token *token) {
    free(token);
}
