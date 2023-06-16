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
    return sourceCodeFile->peek() == EOF && line.length() <= currentCharIndex + 1;
}

/**
 *
 * @return pointer to a token
 */
Token *Lexer::getNextToken() {

    getNextChar();

    // Get rid of spaces
    while (isspace(currentChar)) {
        getNextChar();
    }

    // Get rid of comments
    if (currentChar == '/') {
        getNextChar();
        if (currentChar == '/') {
            readNextLine();
            getNextChar();
        } else {
            if (currentChar == '*') {
                while (true) {
                    getNextChar();
                    if (isEOI()) {
                        lexeme = "";
                        tokenCode = END_OF_INPUT;
                        break;
                    }
                    if (currentChar == '*') {
                        getNextChar();
                        if (currentChar == '/') {
                            getNextChar();
                            lexeme = "";
                            break;
                        }
                    }
                }
            } else {
                tokenCode = DIV;
                lexeme = "/";
                unGetChar();
                return createToken(tokenCode, lexeme, currentLine, currentColumn > 1 ? currentColumn - 1 : 1);
            }
        }
    }

    while (isspace(currentChar)) {
        getNextChar();
    }

    if (isEOI()) {
        tokenCode = END_OF_INPUT;
    }

    switch (currentChar) {
        case '+':
            getNextChar();
            if (currentChar == '+') {
                tokenCode = INC;
                lexeme = "++";
            } else if (currentChar == '=') {
                tokenCode = ADD_ASSIGN;
                lexeme = "+=";
            } else {
                tokenCode = ADD;
                lexeme = "+";
                unGetChar();
            }
            break;
        case '-':
            getNextChar();
            if (currentChar == '-') {
                tokenCode = DEC;
                lexeme = "--";
            } else if (currentChar == '=') {
                tokenCode = SUB_ASSIGN;
                lexeme = "-=";
            } else if (currentChar == '>') {
                tokenCode = ARROW;
                lexeme = "->";
            } else {
                tokenCode = SUB;
                lexeme = "-";
                unGetChar();
            }
            break;
        case '*':
            getNextChar();
            if (currentChar == '=') {
                tokenCode = MULT_ASSIGN;
                lexeme = "*=";
            } else {
                tokenCode = MULT;
                lexeme = "*";
                unGetChar();
            }
            break;
        case '/':
            getNextChar();
            if (currentChar == '=') {
                tokenCode = DIV_ASSIGN;
                lexeme = "/=";
            } else if (currentChar == '*') {
                while (true) {
                    getNextChar();
                    if (isEOI()) {
                        lexeme = "";
                        tokenCode = END_OF_INPUT;
                        break;
                    }
                    if (currentChar == '*') {
                        getNextChar();
                        if (currentChar == '/') {
                            getNextChar();
                            lexeme = "";
                            getNextToken();
                            break;
                        }
                    }
                }
            } else {
                tokenCode = DIV;
                lexeme = "/";
                unGetChar();
            }
            break;
        case '%':
            getNextChar();
            if (currentChar == '=') {
                tokenCode = MOD_ASSIGN;
                lexeme = "%=";
            } else {
                tokenCode = MOD;
                lexeme = "%";
                unGetChar();
            }
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
        case '[':
            tokenCode = LEFT_SQUARE_BRACKET;
            lexeme = "[";
            break;
        case ']':
            tokenCode = RIGHT_SQUARE_BRACKET;
            lexeme = "]";
            break;
        case ',':
            tokenCode = COMMA;
            lexeme = ",";
            break;
        case '.':
            tokenCode = DOT;
            lexeme = ".";
            break;
        case ':':
            tokenCode = COLON;
            lexeme = ":";
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
        case '?':
            getNextChar();
            if (currentChar == '?') {
                tokenCode = NULL_COALISING;
                lexeme = "??";
            } else {
                tokenCode = TERNARY;
                lexeme = "?";
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
        case '~':
            tokenCode = BIT_NOT;
            lexeme = "~";
            break;
        case '^':
            tokenCode = XOR;
            lexeme = "^";
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
            } else if (currentChar == '<') {
                tokenCode = LEFT_SHIFT;
                lexeme = "<<";
            } else {
                tokenCode = LESS_THAN;
                lexeme = "<";
                unGetChar();
            }
            break;
        case '>':
            getNextChar();
            if (currentChar == '=') {
                tokenCode = GREATER_THAN_EQUAL;
                lexeme = ">=";
            } else if (currentChar == '>') {
                tokenCode = RIGHT_SHIFT;
                lexeme = ">>";
            } else {
                tokenCode = GREATER_THAN;
                lexeme = ">";
                unGetChar();
            }
            break;
        default:
            lexeme = "";
            if (isdigit(currentChar)) {
                tokenizeNumber();
            } else if (isalpha(currentChar)) {
                tokenizeIdentifier();
            } else if (currentChar == '"') {
                lexeme += currentChar;
                getNextChar();
                while (currentChar != '"') {
                    lexeme += currentChar;
                    getNextChar();
                }
                lexeme += currentChar;
                tokenCode = STRING_LITERAL;
            } else if (currentChar == '\'') {
                lexeme += currentChar;
                getNextChar();
                while (currentChar != '\'') {
                    lexeme += currentChar;
                    getNextChar();
                }
                lexeme += currentChar;
                tokenCode = CHAR_LITERAL;
            }
    }

    return createToken(tokenCode, lexeme, currentLine, currentColumn - (int) lexeme.length() + 1);
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
    currentColumn--;
    currentCharIndex--;
    currentChar = line[currentCharIndex];
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
    bool isFloatingPoint = false;
    bool isHexadecimal = false;
    bool isOctal = false;
    bool isBinary = false;

    // Check for hexadecimal, octal, and binary prefixes
    if (currentChar == '0') {
        lexeme += currentChar;
        getNextChar();

        if (currentChar == 'x' || currentChar == 'X') {
            lexeme += currentChar;
            getNextChar();
            while (isxdigit(currentChar)) {
                lexeme += currentChar;
                tokenCode = HEX;
                getNextChar();
            }
            if (!isxdigit(currentChar)) {
                unGetChar();
            }
        } else if (currentChar == 'b' || currentChar == 'B') {
            lexeme += currentChar;
            getNextChar();
            while (currentChar == '0' || currentChar == '1') {
                lexeme += currentChar;
                tokenCode = BINARY;
                getNextChar();
            }
            if (currentChar != '0' && currentChar != '1') {
                unGetChar();
            }
        } else {
            while (isOctalDigit(currentChar)) {
                lexeme += currentChar;
                tokenCode = OCTAL;
                getNextChar();
            }
            if (!isOctalDigit(currentChar)) {
                unGetChar();
            }
        }
    } else {
        while (isDigit(currentChar) || currentChar == '_') {
            lexeme += currentChar;
            getNextChar();
        }

        if (currentChar == '.') {
            lexeme += currentChar;
            getNextChar();
            while (isDigit(currentChar)) {
                lexeme += currentChar;
                getNextChar();
            }
            tokenCode = FLOAT_LITERAL;
        } else {
            tokenCode = INT_LITERAL;
        }
        unGetChar();
        return;
    }

}


void Lexer::tokenizeIdentifier() {
    while (isalnum(currentChar)) {
        lexeme += currentChar;
        if (lexeme == "true") {
            tokenCode = TRUE;
        } else if (lexeme == "false") {
            tokenCode = FALSE;
        } else if (lexeme == "boolean") {
            tokenCode = BOOLEAN;
        } else if (lexeme == "char") {
            tokenCode = CHAR;
        } else if (lexeme == "string") {
            tokenCode = STRING;
        } else if (lexeme == "byte") {
            tokenCode = BYTE;
        } else if (lexeme == "list") {
            tokenCode = LIST;
        } else if (lexeme == "map") {
            tokenCode = MAP;
        } else if (lexeme == "array") {
            tokenCode = ARRAY;
        } else if (lexeme == "set") {
            tokenCode = SET;
        } else if (lexeme == "object") {
            tokenCode = OBJECT;
        } else if (lexeme == "json") {
            tokenCode = JSON;
        } else if (lexeme == "class") {
            tokenCode = CLASS;
        } else if (lexeme == "interface") {
            tokenCode = INTERFACE;
        } else if (lexeme == "var") {
            tokenCode = VAR;
        } else if (lexeme == "const") {
            tokenCode = CONST;
        } else if (lexeme == "enum") {
            tokenCode = ENUM;
        } else if (lexeme == "continue") {
            tokenCode = CONTINUE;
        } else if (lexeme == "break") {
            tokenCode = BREAK;
        } else if (lexeme == "switch") {
            tokenCode = SWITCH;
        } else if (lexeme == "case") {
            tokenCode = CASE;
        } else if (lexeme == "foreach") {
            tokenCode = FOR_EACH;
        } else if (lexeme == "throw") {
            tokenCode = THROW;
        } else if (lexeme == "try") {
            tokenCode = TRY;
        } else if (lexeme == "catch") {
            tokenCode = CATCH;
        } else if (lexeme == "finally") {
            tokenCode = FINALLY;
        } else if (lexeme == "return") {
            tokenCode = RETURN;
        } else if (lexeme == "false") {
            tokenCode = FALSE;
        } else if (lexeme == "int") {
            tokenCode = INT;
        } else if (lexeme == "float") {
            tokenCode = FLOAT;
        } else if (lexeme == "void") {
            tokenCode = VOID;
        } else if (lexeme == "if") {
            tokenCode = IF;
        } else if (lexeme == "else") {
            tokenCode = ELSE;
        } else if (lexeme == "while") {
            tokenCode = WHILE;
        } else if (lexeme == "do") {
            tokenCode = DO;
        } else if (lexeme == "for") {
            tokenCode = FOR;
        } else if (lexeme == "print") {
            tokenCode = PRINT;
        } else if (lexeme == "input") {
            tokenCode = INPUT;
        } else {
            tokenCode = IDENTIFIER;
        }
        getNextChar();
    }
    unGetChar();
}

bool Lexer::isOctalDigit(char c) {
    return (c >= '0' && c <= '7');
}