//
// Created by albert on 6/16/23.
//

#include "Parser.h"

Parser::Parser(const std::vector<Token> &tokens)
        : tokens(tokens), currentTokenIndex(0) {
}

void Parser::parse() {
    program();
    // Add additional parsing logic as needed
}

void Parser::program() {
    while (!isAtEnd()) {
        statement();
    }
}

void Parser::statement() {
    if (match(TokenCode::VAR)) {

    } else if (match(TokenCode::PRINT)) {
        // Parse print statement

        // Process the print statement
        // ...

    } else {
        // Handle other statement types
        // ...
    }
}

Expression *Parser::parseExpression() {
    // Parse different expression types (e.g., arithmetic, logical, etc.)
    // Example: Arithmetic expression
    Expression *left = parseTerm();

    while (match(TokenCode::ADD) || match(TokenCode::SUB)) {
        Token operatorToken = previous();
        Expression *right = parseTerm();
        left = new BinaryExpression(operatorToken, left, right);
    }

    return left;
}

Expression *Parser::parseTerm() {
    Expression *left = parseFactor();

    while (match(TokenCode::MULT) || match(TokenCode::DIV)) {
        Token operatorToken = previous();
        Expression *right = parseFactor();
        left = new BinaryExpression(operatorToken, left, right);
    }

    return left;
}

Expression *Parser::parseFactor() {
    if (match(TokenCode::INT_LITERAL)) {
        int value = std::stoi(previous().lexeme);
        return new IntegerLiteralExpression(value);
    } else if (match(TokenCode::IDENTIFIER)) {
        std::string identifier = previous().lexeme;
        return new VariableExpression(identifier);
    } else if (match(TokenCode::LEFT_PAREN)) {
        Expression *expression = parseExpression();
        consume(TokenCode::RIGHT_PAREN);
        return expression;
    } else {
        // Handle other factor types
        // ...
    }
}

Token Parser::consume(TokenCode expectedCode) {
    if (peek().code == expectedCode) {
        return advance();
    } else {
        // Handle mismatched token error
        // You can throw an exception or report an error message here
        // and perform error recovery if needed
        // ...
    }
}

Token Parser::advance() {
    if (!isAtEnd()) {
        currentTokenIndex++;
    }
    return previous();
}

Token Parser::peek() {
    if (!isAtEnd()) {
        return tokens[currentTokenIndex];
    } else {
        // Return an "end-of-input" token to indicate the end of the token stream
//        return Token(TokenCode::END_OF_INPUT, "", 0, 0);
    }
}

Token Parser::previous() const {
    if (currentTokenIndex > 0 && currentTokenIndex <= tokens.size()) {
        return tokens[currentTokenIndex - 1];
    } else {
        // Return an invalid token if there is no previous token
//        return Token(TokenCode::NAL, "", 0, 0);
    }
}

bool Parser::match(TokenCode expectedCode) {
    if (peek().code == expectedCode) {
        advance();
        return true;
    } else {
        return false;
    }
}

bool Parser::isAtEnd() const {
    return currentTokenIndex >= tokens.size();
}
