//
// Created by albert on 6/8/23.
//

#ifndef BOMA_LEXER_H
#define BOMA_LEXER_H

#include <vector>
#include "string"
#include "Token.h"

class Lexer {
public:
    explicit Lexer(string  sourceCode);
    Token* getNextToken();
    std::vector<Token> * getTokens();

private:
    bool isAtEnd();
    char advance();
    bool isDigit(char c);
    bool isAlpha(char c);
    void tokenizeNumber();
    void tokenizeIdentifier();
    bool tokenizeKeyword(const string& word);
    char peek();
    char peekNext();

    const string sourceCode;
    int currentPosition;
    int currentLine;
    int currentColumn;
    string lexeme;
    TokenType tokenType;

};

#endif //BOMA_LEXER_H
