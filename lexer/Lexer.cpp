//
// Created by albert on 6/8/23.
//

#include "Lexer.h"

#include <utility>
#include <iostream>
#include <vector>

Lexer::Lexer(string sourceCode) : sourceCode(std::move(sourceCode)), currentPosition(0), currentLine(1),
                                  currentColumn(1){
}

Token *Lexer::getNextToken() {

    char c = advance();
    lexeme = c;
    switch (c) {
        // Single-character tokens
        case '(':
            tokenType = LEFT_PAREN;
            break;
        case ')':
            tokenType = RIGHT_PAREN;
            break;
        case '{':
            tokenType = LEFT_BRACE;
            break;
        case '}':
            tokenType = RIGHT_BRACE;
            break;
        case ',':
            tokenType = COMMA;
            break;
        case ';':
            tokenType = SEMICOLON;
            break;
        case '+':
            tokenType = PLUS;
            break;
        case '-':
            tokenType = MINUS;
            break;
        case '*':
            tokenType = MULTIPLY;
            break;
        case '/':
            tokenType = DIVIDE;
            break;

            // Ignore whitespace and newline
        case ' ':
        case '\r':
        case '\t':
            lexeme.pop_back();
//            return nullptr;
            break;
        case '\n':
            lexeme.pop_back();
            currentLine++;
            currentColumn = 1;
//            return nullptr;
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

    cout << "LEXEME: " << lexeme << "\t|\tTOKEN: " << tokenType << endl;
    Token * token = (Token*) malloc(sizeof(Token));
    token->lexeme = lexeme;
    token->type = tokenType;
    token->location = *createLocation(currentLine, currentColumn);
//    print(*token);
//    token->location.line = currentLine;
    return token;
    return nullptr;
    return createToken(tokenType, lexeme, currentLine, currentColumn);
}


//vector<Token> *Lexer::getTokens() {
//    auto *tokens = new vector<Token>();
//    while (!isAtEnd()) {
//        char c = advance();
//        lexeme = c;
//        switch (c) {
//            // Single-character tokens
//            case '(':
//                tokenType = LEFT_PAREN;
//                break;
//            case ')':
//                tokenType = RIGHT_PAREN;
//                break;
//            case '{':
//                tokenType = LEFT_BRACE;
//                break;
//            case '}':
//                tokenType = RIGHT_BRACE;
//                break;
//            case ',':
//                tokenType = COMMA;
//                break;
//            case ';':
//                tokenType = SEMICOLON;
//                break;
//            case '+':
//                tokenType = PLUS;
//                break;
//            case '-':
//                tokenType = MINUS;
//                break;
//            case '*':
//                tokenType = MULTIPLY;
//                break;
//            case '/':
//                tokenType = DIVIDE;
//                break;
//
//                // Ignore whitespace and newline
//            case ' ':
//            case '\r':
//            case '\t':
//                lexeme.pop_back();
//                return nullptr;
//                break;
//            case '\n':
//                lexeme.pop_back();
//                currentLine++;
//                currentColumn = 1;
//                return nullptr;
//                break;
//            default:
//                if (isDigit(c)) {
//                    tokenizeNumber();
//                } else if (isAlpha(c)) {
//                    tokenizeIdentifier();
//                } else {
//                    // Handle unexpected character
//                    // ...
//                }
//                break;
//        }
//
//        Token *token = createToken(tokenType, lexeme, currentLine, currentColumn);
//
//        print(*token);
//
//        tokens->push_back(*token);
//    }
//
//    return tokens;
//}

vector<Token> *Lexer::getTokens() {
    auto *tokens = new vector<Token>();
    while (!isAtEnd()) {
        Token token = *getNextToken();
        tokens->push_back(token);
    }
    return tokens;
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

void Lexer::tokenizeNumber() {

}

void Lexer::tokenizeIdentifier() {
    char c = advance();
    while (isAlpha(c)) {
        lexeme += c;
        c = advance();
    }

    if(c == ' ' || c == '\n') {

    } else {
        currentPosition--;
        currentColumn--;
    }

    tokenizeKeyword(lexeme);

}

bool Lexer::tokenizeKeyword(const string &keyword) {
    if (keyword == "var") {
        tokenType = VAR;
    } else if (keyword == "function") {
        tokenType = FUNCTION;
    } else if (keyword == "return") {
        tokenType = RETURN;
    } else if (keyword == "const") {
        tokenType = CONST;
    } else if (keyword == "if") {
        tokenType = IF;
    } else if (keyword == "else") {
        tokenType = ELSE;
    } else if (keyword == "elif") {
        tokenType = ELIF;
    } else if (keyword == "while") {
        tokenType = WHILE;
    } else if (keyword == "do") {
        tokenType = DO;
    } else if (keyword == "for") {
        tokenType = FOR;
    } else if (keyword == "char") {
        tokenType = CHAR;
    } else if (keyword == "string") {
        tokenType = STRING;
    } else if (keyword == "float") {
        tokenType = FLOAT;
    } else if (keyword == "int") {
        tokenType = INT;
    } else if (keyword == "enum") {
        tokenType = ENUM;
    } else if (keyword == "continue") {
        tokenType = CONTINUE;
    } else if (keyword == "break") {
        tokenType = BREAK;
    } else if (keyword == "true") {
        tokenType = TRUE;
    } else if (keyword == "false") {
        tokenType = FALSE;
    } else {
        tokenType = IDENTIFIER;
        return false;
    }
    return true;
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
