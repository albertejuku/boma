//
// Created by albert on 6/8/23.
//

#ifndef BOMA_TOKEN_H
#define BOMA_TOKEN_H

#include "string"

#include "Location.h"

using namespace std;

typedef enum {
    // Single-character tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, SEMICOLON,

    // Arithmetic operators
    PLUS, MINUS, MULTIPLY, DIVIDE,

    // Literals
    NUMBER, IDENTIFIER,

    // Keywords
    FUNCTION, VAR, RETURN, CONST, IF, ELSE, ELIF, WHILE, DO, FOR,
    CHAR, STRING, FLOAT, INT, ENUM, CONTINUE, BREAK, TRUE, FALSE,

    // End-of-file
    END_OF_FILE
} TokenType;

typedef struct {
    TokenType type;
    string lexeme;
    Location location;
} Token;

void print(Token *token);

Token *createToken(TokenType type, string lexeme, int line, int column);

void freeToken(Token *token);

#endif //BOMA_TOKEN_H
