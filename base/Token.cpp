//
// Created by albert on 6/8/23.
//

#include <cstdlib>
#include <cstring>
#include <utility>
#include "Token.h"

Token *createToken(TokenType type, string lexeme, int line, int column) {
    auto *token = (Token *) malloc(sizeof(Token));
    token->type = type;
    token->lexeme = std::move(lexeme);
    token->location = *createLocation(line, column);
    return token;
}

void freeToken(Token *token) {
    free(token);
}
