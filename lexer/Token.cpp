//
// Created by albert on 6/8/23.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <utility>
#include "Token.h"


string tokenList[] = {"LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
                      "COMMA", "SEMICOLON",

        // Arithmetic operators
                      "PLUS", "MINUS", "MULTIPLY", "DIVIDE",

        // Literals
                      "NUMBER", "IDENTIFIER",

        // Keywords
                      "FUNCTION", "VAR", "RETURN",  "CONST", "IF", "ELSE", "ELIF", "WHILE", "DO", "FOR",
                      "CHAR", "STRING", "FLOAT", "INT", "ENUM", "CONTINUE", "BREAK", "TRUE", "FALSE",

        // End-of-file
                      "END_OF_FILE"};


Token* createToken(TokenType type, const string& lexeme, int line, int column) {
    auto* token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->lexeme = lexeme;
    token->location = *createLocation(line, column);
    return token;
}


void print(const Token& token) {
    std::cout << "{ " << tokenList[token.type] << ", " << token.lexeme << ", " << token.location.line << ":" << token.location.column << " }" << endl;
}

void freeToken(Token *token) {
    free(token);
}
