#include <iostream>

#include "lexer/Lexer.h"

int main() {
    string s = "int age is var name = 'Albert';";
    Lexer lexer(s);
//    while((token = lexer.getTokens()) != nullptr) {
//        print(token);
//    }
    vector<Token> *tokens = lexer.getTokens();
    for (Token &item: *tokens) {
        print(item);
    }
    cout << "LENGTH: " << tokens->size() << endl;
    cout << "This has been the end." << endl;
    return 0;
}
