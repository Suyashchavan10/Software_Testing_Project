#include "../../src/tokenizer/tokenizer.h" // Header for the Tokenizer class
#include <gtest/gtest.h> // GoogleTest header
using namespace std;

// Test tokenizeNumber() method
TEST(TokenizerTest, TokenizeNumber) {
    string input = "12345";
    Tokenizer tokenizer(input);
    auto tokens = tokenizer.tokenize();

    ASSERT_EQ(tokens.size(), 2); // One number token + END_OF_FILE token
    EXPECT_EQ(tokens[0].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[0].lexeme, "12345");
}

// Test tokenizeIdentifier() method
TEST(TokenizerTest, TokenizeIdentifier) {
    // Input includes various keywords, identifiers, operators, and literals
    string input = R"(
        Declare x As Integer
        Declare arr As Array Of Integer[5]
        Assign x = 5
        Print "Hello"
        If x > 0 Then
            Assign x = x + 1
        Else
            Assign x = 0
        End If
        For i=0 To 5 Do
            Assign arr[i] = i * 2
        End For
        While x < 10 Do
            Assign x = x + 1
        End While
    )";

    Tokenizer tokenizer(input);
    auto tokens = tokenizer.tokenize();

    // Verify the total number of tokens
    ASSERT_EQ(tokens.size(), 65); 

    // Verify keywords and identifiers
    EXPECT_EQ(tokens[0].type, TokenType::DECLARE);    // Declare
    EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER); // x
    EXPECT_EQ(tokens[2].type, TokenType::KEYWORD);    // As
    EXPECT_EQ(tokens[3].type, TokenType::INTEGER);    // Integer

    EXPECT_EQ(tokens[4].type, TokenType::DECLARE);    // Declare (for arr)
    EXPECT_EQ(tokens[5].type, TokenType::IDENTIFIER); // arr
    EXPECT_EQ(tokens[6].type, TokenType::KEYWORD);    // As
    EXPECT_EQ(tokens[7].type, TokenType::ARRAY);      // Array
    EXPECT_EQ(tokens[8].type, TokenType::KEYWORD);    // Of
    EXPECT_EQ(tokens[9].type, TokenType::INTEGER);    // Integer
    EXPECT_EQ(tokens[10].type, TokenType::NUMBER);    // 5

    // Verify assignments
    EXPECT_EQ(tokens[11].type, TokenType::ASSIGN);    // Assign
    EXPECT_EQ(tokens[12].type, TokenType::IDENTIFIER); // x
    EXPECT_EQ(tokens[13].type, TokenType::OPERATOR);  // =
    EXPECT_EQ(tokens[14].type, TokenType::NUMBER);    // 5

    // Verify print statement
    EXPECT_EQ(tokens[15].type, TokenType::PRINT);     // Print
    EXPECT_EQ(tokens[16].type, TokenType::STRINGVAL); // Hello

    // Verify conditional keywords
    EXPECT_EQ(tokens[17].type, TokenType::IF);        // If
    EXPECT_EQ(tokens[18].type, TokenType::IDENTIFIER); // x
    EXPECT_EQ(tokens[19].type, TokenType::OPERATOR);  // >
    EXPECT_EQ(tokens[20].type, TokenType::NUMBER);    // 0
    EXPECT_EQ(tokens[21].type, TokenType::KEYWORD);   // Then

    EXPECT_EQ(tokens[22].type, TokenType::ASSIGN);    // Assign
    EXPECT_EQ(tokens[23].type, TokenType::IDENTIFIER); // x
    EXPECT_EQ(tokens[24].type, TokenType::OPERATOR);  // =
    EXPECT_EQ(tokens[25].type, TokenType::IDENTIFIER); // x
    EXPECT_EQ(tokens[26].type, TokenType::OPERATOR);  // +
    EXPECT_EQ(tokens[27].type, TokenType::NUMBER);    // 1

    EXPECT_EQ(tokens[28].type, TokenType::ELSE);      // Else
    EXPECT_EQ(tokens[29].type, TokenType::ASSIGN);    // Assign
    EXPECT_EQ(tokens[30].type, TokenType::IDENTIFIER); // x
    EXPECT_EQ(tokens[31].type, TokenType::OPERATOR);  // =
    EXPECT_EQ(tokens[32].type, TokenType::NUMBER);    // 0

    EXPECT_EQ(tokens[33].type, TokenType::END);       // End
    EXPECT_EQ(tokens[34].type, TokenType::IF);        // If

    // Verify loops
    EXPECT_EQ(tokens[35].type, TokenType::FOR);       // For
    EXPECT_EQ(tokens[36].type, TokenType::IDENTIFIER); // i
    EXPECT_EQ(tokens[37].type, TokenType::OPERATOR);  // =
    EXPECT_EQ(tokens[38].type, TokenType::NUMBER);    // 0
    EXPECT_EQ(tokens[39].type, TokenType::KEYWORD);   // To
    EXPECT_EQ(tokens[40].type, TokenType::NUMBER);    // 5
    EXPECT_EQ(tokens[41].type, TokenType::KEYWORD);   // Do

    EXPECT_EQ(tokens[42].type, TokenType::ASSIGN);    // Assign
    EXPECT_EQ(tokens[43].type, TokenType::IDENTIFIER); // arr
    EXPECT_EQ(tokens[44].type, TokenType::IDENTIFIER); // i
    EXPECT_EQ(tokens[45].type, TokenType::OPERATOR);  // =
    EXPECT_EQ(tokens[46].type, TokenType::IDENTIFIER); // i
    EXPECT_EQ(tokens[47].type, TokenType::OPERATOR);  // *
    EXPECT_EQ(tokens[48].type, TokenType::NUMBER);    // 2

    EXPECT_EQ(tokens[49].type, TokenType::END);       // End
    EXPECT_EQ(tokens[50].type, TokenType::FOR);       // For

    // Verify while loop
    EXPECT_EQ(tokens[51].type, TokenType::WHILE);     // While
    EXPECT_EQ(tokens[52].type, TokenType::IDENTIFIER); // x
    EXPECT_EQ(tokens[53].type, TokenType::OPERATOR);  // <
    EXPECT_EQ(tokens[54].type, TokenType::NUMBER);    // 10
    EXPECT_EQ(tokens[55].type, TokenType::KEYWORD);   // Do

    EXPECT_EQ(tokens[62].type, TokenType::END);       // End
    EXPECT_EQ(tokens[63].type, TokenType::WHILE);     // While
}

// Test tokenizeOperator() method
TEST(TokenizerTest, TokenizeOperator) {
    string input = "x = 5 + 10";
    Tokenizer tokenizer(input);
    auto tokens = tokenizer.tokenize();

    ASSERT_EQ(tokens.size(), 6); // x, =, 5, +, 10, END_OF_FILE
    EXPECT_EQ(tokens[1].type, TokenType::OPERATOR);
    EXPECT_EQ(tokens[1].lexeme, "=");
    EXPECT_EQ(tokens[3].type, TokenType::OPERATOR);
    EXPECT_EQ(tokens[3].lexeme, "+");
}

// Test tokenizeString() method
TEST(TokenizerTest, TokenizeString) {
    string input = "\"Hello, World!\"";
    Tokenizer tokenizer(input);
    auto tokens = tokenizer.tokenize();

    ASSERT_EQ(tokens.size(), 2); // String token + END_OF_FILE token
    EXPECT_EQ(tokens[0].type, TokenType::STRINGVAL);
    EXPECT_EQ(tokens[0].lexeme, "Hello, World!");
}

// Test tokenizeOther() method (default case handling)
TEST(TokenizerTest, TokenizeOther) {
    string input = ";";
    Tokenizer tokenizer(input);
    auto tokens = tokenizer.tokenize();

    ASSERT_EQ(tokens.size(), 1); // Only END_OF_FILE token
    EXPECT_EQ(tokens[0].type, TokenType::END_OF_FILE);
}

// Comprehensive test for tokenize() method
TEST(TokenizerTest, ComprehensiveTokenize) {
    string input = "Declare x As Integer\nx = 5 + 10";
    Tokenizer tokenizer(input);
    auto tokens = tokenizer.tokenize();

    ASSERT_EQ(tokens.size(), 10); // Declare, x, As, Integer, x, =, 5, +, 10, END_OF_FILE
    EXPECT_EQ(tokens[0].type, TokenType::DECLARE);
    EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[2].type, TokenType::KEYWORD);
    EXPECT_EQ(tokens[3].type, TokenType::INTEGER);
    EXPECT_EQ(tokens[4].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[5].type, TokenType::OPERATOR);
    EXPECT_EQ(tokens[6].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[7].type, TokenType::OPERATOR);
    EXPECT_EQ(tokens[8].type, TokenType::NUMBER);
}

// Test handling of whitespace
TEST(TokenizerTest, HandleWhitespace) {
    string input = " \t\nDeclare    x   As Integer";
    Tokenizer tokenizer(input);
    auto tokens = tokenizer.tokenize();

    ASSERT_EQ(tokens.size(), 5); // Declare, x, As, Integer, END_OF_FILE
    EXPECT_EQ(tokens[0].type, TokenType::DECLARE);
    EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[2].type, TokenType::KEYWORD);
    EXPECT_EQ(tokens[3].type, TokenType::INTEGER);
}

