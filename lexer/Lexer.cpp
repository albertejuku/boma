//
// Created by albert on 6/8/23.
//

#include "Lexer.h"

#include <utility>
#include <iostream>
#include <vector>
#include<fstream>

Lexer::Lexer(ifstream *scf) {
    sourceCodeFile = scf;
    currentPosition = 0;
    currentLine = 0;
    currentColumn = 0;
    lexeme = "";
    line = "\n";
    currentChar = '\n';
    tokenCode = IDENTIFIER;
    currentCharIndex = 0;
}

bool Lexer::isEOI() {
    return sourceCodeFile->peek() == EOF;
}

/**
 *
 * @return pointer to a token
 */
Token *Lexer::getNextToken() {
    getNextChar();

    while (isspace(currentChar) || currentChar == '/') {
        if (currentChar == '/') {
            getNextChar();
            if (currentChar == '/') {
                readNextLine();
            } else {
                tokenCode = SLASH;
                lexeme = "/";
                return createToken(tokenCode, lexeme, currentLine, currentColumn - 1);
            }
        } else {
            getNextChar();
        }
    }

    if (isEOI()) {
        tokenCode = END_OF_INPUT;
    }

    switch (currentChar) {
        case '+':
            tokenCode = PLUS;
            lexeme = "+";
            break;
        case '-':
            tokenCode = MINUS;
            lexeme = "-";
            break;
        case '*':
            tokenCode = TIMES;
            lexeme = "*";
            break;
        case '%':
            tokenCode = MOD;
            lexeme = "%";
            break;
        case '(':
            tokenCode = LEFT_PAREN;
            lexeme = "(";
            break;
        case ')':
            tokenCode = RIGHT_PAREN;
            lexeme = ")";
            break;
        case '{':
            tokenCode = LEFT_BRACE;
            lexeme = "{";
            break;
        case '}':
            tokenCode = RIGHT_BRACE;
            lexeme = "}";
            break;
        case ',':
            tokenCode = COMMA;
            lexeme = ",";
            break;
        case ';':
            tokenCode = SEMICOLON;
            lexeme = ";";
            break;
        case '|':
            getNextChar();
            if (currentChar == '|') {
                tokenCode = OR;
                lexeme = "||";
            } else {
                tokenCode = BIT_OR;
                lexeme = "|";
                unGetChar();
            }
            break;
        case '&':
            getNextChar();
            if (currentChar == '&') {
                tokenCode = AND;
                lexeme = "&&";
            } else {
                tokenCode = BIT_AND;
                lexeme = "&";
                unGetChar();
            }
            break;
        case '=':
            getNextChar();
            if (currentChar == '=') {
                tokenCode = EQUALS;
                lexeme = "==";
            } else {
                tokenCode = ASSIGN;
                lexeme = "=";
                unGetChar();
            }
            break;
        case '!':
            getNextChar();
            if (currentChar == '=') {
                tokenCode = NOT_EQUALS;
                lexeme = "!=";
            } else {
                tokenCode = NOT;
                lexeme = "!";
                unGetChar();
            }
            break;
        case '<':
            getNextChar();
            if (currentChar == '=') {
                tokenCode = LESS_THAN_EQUAL;
                lexeme = "<=";
            } else {
                tokenCode = LESS;
                lexeme = "<";
                unGetChar();
            }
            break;
        case '>':
            getNextChar();
            if (currentChar == '=') {
                tokenCode = GREATER_THAN_EQUAL;
                lexeme = ">=";
            } else {
                tokenCode = GREATER;
                lexeme = ">";
                unGetChar();
            }
            break;
        default:
            lexeme = "";
            if (isdigit(currentChar)) {
                tokenCode = INT_LITERAL;
                while (isdigit(currentChar)) {
                    lexeme += currentChar;
                    getNextChar();
                }
                if (!isdigit(currentChar)) {
                    currentCharIndex -= 1;
                }
            } else if (isalpha(currentChar)) {
                while (isalnum(currentChar)) {
                    lexeme += currentChar;
                    if (lexeme == "true") {
                        tokenCode = TRUE;
                        break;
                    } else if (lexeme == "boolean") {
                        tokenCode = BOOLEAN;
                    } else if (lexeme == "main") {
                        tokenCode = IDENTIFIER;
                        break;
                    } else if (lexeme == "return") {
                        tokenCode = RETURN;
                        break;
                    } else if (lexeme == "false") {
                        tokenCode = FALSE;
                        break;
                    } else if (lexeme == "int") {
                        tokenCode = INT;
                        break;
                    } else if (lexeme == "float") {
                        tokenCode = FLOAT;
                        break;
                    } else if (lexeme == "void") {
                        tokenCode = VOID;
                        break;
                    } else if (lexeme == "if") {
                        tokenCode = IF;
                        break;
                    } else if (lexeme == "else") {
                        tokenCode = ELSE;
                        break;
                    } else if (lexeme == "while") {
                        tokenCode = WHILE;
                        break;
                    } else if (lexeme == "do") {
                        tokenCode = DO;
                    } else if (lexeme == "for") {
                        tokenCode = FOR;
                    } else if (lexeme == "print") {
                        tokenCode = PRINT;
                    } else if (lexeme == "input") {
                        tokenCode = INPUT;
                    } else {
                        tokenCode = NAL;
                    }
                    getNextChar();
                }
                unGetChar();
            }
    }

    return createToken(tokenCode, lexeme, currentLine, currentColumn - (int) lexeme.length());
}


vector<Token> *Lexer::getTokens() {
    auto *tokens = new vector<Token>();
    while (!isEOI()) {
        Token token = *getNextToken();
        tokens->push_back(token);
    }
    return tokens;
}

void Lexer::getNextChar() {
    if (currentCharIndex < line.length()) {
        currentChar = line[currentCharIndex];
        currentCharIndex += 1;
        currentColumn += 1;
    } else if (!sourceCodeFile->eof()) {
        readNextLine();
        getNextChar();
    } else {
        currentChar = EOF;
    }
}

void Lexer::unGetChar() {
    if(currentCharIndex > 0) {
        currentColumn--;
        currentCharIndex--;
        currentChar = line[currentCharIndex];
    }
}

void Lexer::readNextLine() {
    if (getline(*sourceCodeFile, line)) {
        currentCharIndex = 0;
        currentColumn = 0;
        currentLine++;
    } else {
        line = "";
    }
}

bool Lexer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Lexer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

void Lexer::tokenizeNumber() {

}

void Lexer::tokenizeIdentifier() {
    getNextChar();
    while (isAlpha(currentChar)) {
        lexeme += currentChar;
        getNextChar();
    }

    if (currentChar == ' ' || currentChar == '\n') {

    } else {
        currentPosition--;
        currentColumn--;
    }

    tokenizeKeyword(lexeme);

}

void Lexer::tokenizeKeyword(const std::string &word) {

}