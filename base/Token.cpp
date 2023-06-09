//
// Created by albert on 6/8/23.
//

#include <cstdlib>
#include <cstring>
#include "Token.h"

Token* createToken(TokenType type, const char* lexeme, int line, int column) {
    auto* token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->lexeme = strdup(lexeme);
    token->location = *createLocation(line, column);
    return token;
}

void freeToken(Token* token) {
    free(token->lexeme);
    free(token);
}
