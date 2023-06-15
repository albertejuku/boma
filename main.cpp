#include <iostream>

#include "lexer/Lexer.h"

int main() {
    string s = "var name: string = 'Albert';";
    Lexer lexer(s);

    vector<Token> *tokens = lexer.getTokens();
    for (Token &item: *tokens) {
        print(item);
    }
    cout << "LENGTH: " << tokens->size() << endl;
    cout << "This has been the end." << endl;
    return 0;
}
