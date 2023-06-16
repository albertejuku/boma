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
    Lexer(ifstream*);
    Token* getNextToken();
    std::vector<Token> * getTokens();

private:
    bool isDigit(char c);
    bool isAlpha(char c);
    void tokenizeNumber();
    void tokenizeIdentifier();
    bool isEOI();
    void getNextChar();
    void readNextLine();
    void unGetChar();

    ifstream *sourceCodeFile;
    int currentPosition;
    int currentLine;
    int currentColumn;
    int currentCharIndex;
    string lexeme;
    TokenCode tokenCode;
    string line;
    char currentChar;


    bool isOctalDigit(char c);
};

#endif //BOMA_LEXER_H
