//
// Created by albert on 6/8/23.
//

#ifndef BOMA_LEXER_H
#define BOMA_LEXER_H

#include "string"
#include "Token.h"

class Lexer {
public:
    explicit Lexer(string  sourceCode);
    Token* getNextToken();
private:
    bool isAtEnd();
    char advance();
    bool isDigit(char c);
    bool isAlpha(char c);
    void addToken(TokenType type);
    void tokenizeNumber();
    void tokenizeIdentifier();
    char peek();
    char peekNext();

    const string sourceCode;
    int currentPosition;
    int currentLine;
    int currentColumn;
};

#endif //BOMA_LEXER_H
