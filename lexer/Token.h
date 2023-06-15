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
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, LEFT_SQUARE_BRACKET, RIGHT_SQUARE_BRACKET, GREATER, LESS,
    ASTERISK, DOLLAR, CARET, NOT, SLASH, AMPERSAND,
    COMMA, SEMICOLON, COLON,

    ARROW,

    // Arithmetic operators
    PLUS, MINUS, MULTIPLY, DIVIDE, TIMES,
    ADD, SUB, MULT, DIV, MOD, INC, DEC,
    ASSIGN, ADD_ASSIGN, SUB_ASSIGN, MULT_ASSIGN, MOD_ASSIGN, DIV_ASSIGN,
    EQUALS, NOT_EQUALS, GREATER_THAN, LESS_THAN, GREATER_THAN_EQUAL, LESS_THAN_EQUAL,
    AND, OR, BIT_AND, BIT_OR, BIT_NOT, XOR, LEFT_SHIFT, RIGHT_SHIFT,
    TERNARY, DOT, BOMA_NULL, NULL_COALISING,

    // Literals
    IDENTIFIER, CHAR, STRING, FLOAT, INT, BYTE, BOOLEAN, TRUE, FALSE, HEX, OCTAL, BINARY, INT_LITERAL, STRING_LITERAL, CHAR_LITERAL, BYTE_LITERAL,
    LIST, ARRAY, SET, MAP, OBJECT, JSON,
    CLASS, INTERFACE,

    // Keywords
    VAR, RETURN, CONST,
    VOID, PRINT, INPUT,
    ENUM, CONTINUE, BREAK,

    // Control flow
    IF, ELSE, ELSE_IF, WHILE, DO, FOR, SWITCH, CASE, FOR_EACH,
    THROW, TRY_CATCH, FINALLY,

    NAL,
    // End-of-file
    END_OF_INPUT
} TokenCode;

typedef struct {
    TokenCode code;
    std::string lexeme;
    Location location;
} Token;

void print(const Token& token);

Token *createToken(TokenCode code, const string& lexeme, int line, int column);

void freeToken(Token *token);

#endif //BOMA_TOKEN_H
