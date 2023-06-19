//
// Created by albert on 6/16/23.
//

#ifndef BOMA_PARSER_H
#define BOMA_PARSER_H


#include <vector>
#include <string>

#include "../lexer/Token.h"

class Parser {
public:
    Parser(const std::vector<Token>& tokens);

    // Public methods to start the parsing process
    void parse();

private:
    // Private methods for grammar rules
    void program();
    void statement();
    void expression();
    // Add more grammar rules here

    // Utility methods for token manipulation
    Token consume();
    bool match(TokenCode expectedCode);
    Token peek();
    bool isAtEnd() const;

    // Member variables
    std::vector<Token> tokens;
    size_t currentTokenIndex;

    Token previous() const;

    Token advance();

    Token consume(TokenCode expectedCode);
};

#endif //BOMA_PARSER_H
