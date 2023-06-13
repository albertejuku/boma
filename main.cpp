#include <iostream>

#include "base/Lexer.h"

int main() {
    string s = "int main() {};";
    Lexer lexer(s);
    Token *token;
//    while((token = lexer.getTokens()) != nullptr) {
//        print(token);
//    }

    lexer.getTokens();

    cout << "This has been the end." << endl;
    return 0;
}
