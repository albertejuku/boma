#include <iostream>
#include <fstream>

#include "lexer/Lexer.h"

int main(int argc, char **argv) {

    if(argc < 2) {
        cout << "Usage: " << argv[0] << " input_file.boma" << endl;
        return -1;
    }


    auto *sourceCode = new ifstream();
    sourceCode->open(argv[1], ifstream::in);
    if(sourceCode->is_open()) {
        Lexer lexer(sourceCode);

        vector<Token> *tokens = lexer.getTokens();
        for (Token &item: *tokens) {
            print(item);
        }
        cout << "LENGTH: " << tokens->size() << endl;

        tokens->clear();

    }

    cout << "This has been the end." << endl;
    return 0;
}
