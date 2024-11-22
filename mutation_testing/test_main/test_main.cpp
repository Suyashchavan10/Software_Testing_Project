#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>

#include "../../src/codeGenerator/codeGenerator.cpp"
#include "../../src/parser/parser.h"
#include "../../src/tokenizer/tokenizer.h"
using namespace std;

bool validateTokens(const vector<Token>& tokens, const vector<pair<TokenType, string>>& expectedTokens) {
    if (tokens.size() != expectedTokens.size()) {
        return false;
    }
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i].type != expectedTokens[i].first || tokens[i].lexeme != expectedTokens[i].second) {
            return false;
        }
    }
    return true;
}

bool checkGeneratedCode(const string& generatedCode, const string& expectedCode) {
    auto normalizeWhitespace = [](const string& str) {
        string result;
        istringstream iss(str);
        string line;

        // Skip leading empty lines
        while (getline(iss, line)) {
            line.erase(0, line.find_first_not_of(" \t"));
            if (!line.empty()) { 
                result += line + "\n";
                break;
            }
        }

        // Process the remaining lines
        while (getline(iss, line)) {
            line.erase(0, line.find_first_not_of(" \t"));
            line.erase(line.find_last_not_of(" \t") + 1);
            result += line + "\n";
        }

        // Remove the trailing newline, if present
        while (!result.empty() && result.back() == '\n') {
            result.pop_back();
        }

        return result;
    };

    return normalizeWhitespace(generatedCode) == normalizeWhitespace(expectedCode);
}

int main() {
    // Test pseudocode input
    string pseudocode = R"(
        Declare x As Integer
        Assign x = 5
        Print x
    )";

    // Expected tokens
    vector<pair<TokenType, string>> expectedTokens = {
        {TokenType::DECLARE, "Declare"},
        {TokenType::IDENTIFIER, "x"},
        {TokenType::KEYWORD, "As"},
        {TokenType::INTEGER, "Integer"},
        {TokenType::ASSIGN, "Assign"},
        {TokenType::IDENTIFIER, "x"},
        {TokenType::OPERATOR, "="},
        {TokenType::NUMBER, "5"},
        {TokenType::PRINT, "Print"},
        {TokenType::IDENTIFIER, "x"},
        {TokenType::END_OF_FILE, ""}
    };

    // Expected generated code
    string expectedGeneratedCode = R"(
        #include <bits/stdc++.h>
        using namespace std;

        int main() {
            int x;
            x = 5;
            cout << x << endl;
            return 0;
        }
    )";

    Tokenizer tokenizer(pseudocode);
    vector<Token> tokens = tokenizer.tokenize();

    // Validate token generation
    assert(validateTokens(tokens, expectedTokens) && "Token generation failed!");
    Parser parser(tokens);
    Node ast = parser.parse();

    // Validate AST structure (basic validation by ensuring node types are correct)
    assert(ast.type == NodeType::DECLARATION && "Root node is not a declaration!");
    CodeGenerator generator;
    string generatedCode = generator.generateCode(ast);

    // Validate code generation
    assert(checkGeneratedCode(generatedCode, expectedGeneratedCode) && "Code generation failed!");

    cout << "All tests passed successfully!" << endl;

    return 0;
}
