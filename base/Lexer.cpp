//
// Created by albert on 6/8/23.
//

#include "Lexer.h"

#include <utility>

Lexer::Lexer(string sourceCode) : sourceCode(std::move(sourceCode)), currentPosition(0), currentLine(1), currentColumn(1) {
    this->lexeme = "";
}

Token *Lexer::getNextToken() {

    while (!isAtEnd()) {
        char c = advance();
        lexeme += c;
        switch (c) {
            // Single-character tokens
            case '(':
                addToken(LEFT_PAREN);
                break;
            case ')':
                addToken(RIGHT_PAREN);
                break;
            case '{':
                addToken(LEFT_BRACE);
                break;
            case '}':
                addToken(RIGHT_BRACE);
                break;
            case ',':
                addToken(COMMA);
                break;
            case ';':
                addToken(SEMICOLON);
                break;
            case '+':
                addToken(PLUS);
                break;
            case '-':
                addToken(MINUS);
                break;
            case '*':
                addToken(MULTIPLY);
                break;
            case '/':
                addToken(DIVIDE);
                break;

                // Ignore whitespace and newline
            case ' ':
            case '\r':
            case '\t':
                lexeme.pop_back();
                break;
            case '\n':
                lexeme.pop_back();
                currentLine++;
                currentColumn = 1;
                break;
            default:
                if (isDigit(c)) {
                    tokenizeNumber();
                } else if (isAlpha(c)) {
                    tokenizeIdentifier();
                } else {
                    // Handle unexpected character
                    // ...
                }
                break;
        }
    }

    return createToken(END_OF_FILE, lexeme, currentLine, currentColumn);
}

bool Lexer::isAtEnd() {
    return currentPosition >= sourceCode.length();
}

char Lexer::advance() {
    char c = sourceCode[currentPosition++];
    currentColumn++;
    return c;
}

bool Lexer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Lexer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

void Lexer::addToken(TokenType type) {

}

void Lexer::tokenizeNumber() {

}

void Lexer::tokenizeIdentifier() {

}

char Lexer::peek() {
    if (isAtEnd()) {
        return '\0';
    }
    return sourceCode[currentPosition];
}

char Lexer::peekNext() {
    if (currentPosition + 1 >= sourceCode.length()) {
        return '\0';
    }
    return sourceCode[currentPosition + 1];
}
