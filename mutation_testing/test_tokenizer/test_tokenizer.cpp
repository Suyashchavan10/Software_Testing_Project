// #include "../../src/tokenizer/tokenizer.h" // Header for the Tokenizer class
#include "../../src/tokenizer/tokenizer.cpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Helper function to check if the token matches the expected values
bool checkToken(const Token& token, TokenType expectedType, const string& expectedLexeme) {
    return token.type == expectedType && token.lexeme == expectedLexeme;
}

int main() {
    // Test Case 1: Tokenize numbers
    {
        string input = "12345";
        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();

        if (tokens.size() != 2 || !checkToken(tokens[0], TokenType::NUMBER, "12345")) {
            return 1; // Test failed
        }
    }

    // Test Case 2: Tokenize identifiers and keywords
    {
        string input = "Declare x As Integer";
        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();

        if (tokens.size() != 5 || 
            !checkToken(tokens[0], TokenType::DECLARE, "Declare") ||
            !checkToken(tokens[1], TokenType::IDENTIFIER, "x") ||
            !checkToken(tokens[2], TokenType::KEYWORD, "As") ||
            !checkToken(tokens[3], TokenType::INTEGER, "Integer")) {
            return 1; // Test failed
        }
    }

    // Test Case 3: Tokenize operators
    {
        string input = "x = 5 + 10";
        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();

        if (tokens.size() != 6 || 
            !checkToken(tokens[1], TokenType::OPERATOR, "=") ||
            !checkToken(tokens[3], TokenType::OPERATOR, "+")) {
            return 1; // Test failed
        }
    }

    // Test Case 4: Tokenize strings
    {
        string input = "\"Hello, World!\"";
        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();

        if (tokens.size() != 2 || !checkToken(tokens[0], TokenType::STRINGVAL, "Hello, World!")) {
            return 1; // Test failed
        }
    }

    // Test Case 5: Tokenize mixed input with keywords and literals
    {
        string input = "If x > 0 Then Print \"Positive\" Else Print \"Negative\" End If";
        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();

        if (tokens.size() != 13 ||
            !checkToken(tokens[0], TokenType::IF, "If") ||
            !checkToken(tokens[5], TokenType::PRINT, "Print") ||
            !checkToken(tokens[6], TokenType::STRINGVAL, "Positive") ||
            !checkToken(tokens[9], TokenType::PRINT, "Print") ||
            !checkToken(tokens[10], TokenType::STRINGVAL, "Negative") ||
            !checkToken(tokens[11], TokenType::END, "End")) {
            return 1; // Test failed
        }
    }

    // Test Case 6: Tokenize array declarations
    {
        string input = "Declare arr As Array Of Integer[5]";
        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();

        if (tokens.size() != 11 ||
            !checkToken(tokens[0], TokenType::DECLARE, "Declare") ||
            !checkToken(tokens[1], TokenType::IDENTIFIER, "arr") ||
            !checkToken(tokens[3], TokenType::ARRAY, "Array") ||
            !checkToken(tokens[5], TokenType::INTEGER, "Integer") ||
            !checkToken(tokens[6], TokenType::NUMBER, "5")) {
            return 1; // Test failed
        }
    }

    // Test Case 7: Tokenize whitespace-only input
    {
        string input = "   \t  \n  ";
        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();

        if (tokens.size() != 1 || tokens[0].type != TokenType::END_OF_FILE) {
            return 1; // Test failed
        }
    }

    // Test Case 8: Tokenize unrecognized characters
    {
        string input = "$%^&";
        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();

        if (tokens.size() != 1 || tokens[0].type != TokenType::END_OF_FILE) {
            return 1; // Test failed
        }
    }

    // All tests passed
    return 0;
}
