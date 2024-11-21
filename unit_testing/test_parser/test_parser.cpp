#include "../../src/tokenizer/tokenizer.h" // Header for the Tokenizer class
#include "../../src/parser/parser.h" // Header for the Parser class
#include <gtest/gtest.h> // GoogleTest header
using namespace std;

// Helper function to tokenize input pseudocode
vector<Token> tokenizeInput(const string& input) {
    Tokenizer tokenizer(input);
    return tokenizer.tokenize();
}

// Test parsing declarations
TEST(ParserTest, ParseDeclaration) {
    string input = "Declare x As Integer";
    auto tokens = tokenizeInput(input);
    Parser parser(tokens);

    Node ast = parser.parse();
    ASSERT_EQ(ast.children.size(), 1);
    Node declaration = ast.children[0];

    EXPECT_EQ(declaration.type, NodeType::DECLARATION);
    ASSERT_EQ(declaration.children.size(), 2); // Identifier and Type
    EXPECT_EQ(declaration.children[0].token.lexeme, "x");   // Identifier
    EXPECT_EQ(declaration.children[1].token.lexeme, "Integer"); // Type
}

// Test parsing array declarations
TEST(ParserTest, ParseArrayDeclaration) {
    string input = "Declare arr As Array Of Integer[5]";
    auto tokens = tokenizeInput(input);
    Parser parser(tokens);

    Node ast = parser.parse();
    ASSERT_EQ(ast.children.size(), 1);
    Node declaration = ast.children[0];

    EXPECT_EQ(declaration.type, NodeType::DECLARATION);
    ASSERT_EQ(declaration.children.size(), 4); // Identifier, Type, Data Type, and Array Size
    EXPECT_EQ(declaration.children[0].token.lexeme, "arr"); // Identifier
    EXPECT_EQ(declaration.children[1].token.lexeme, "Array"); // Type
    EXPECT_EQ(declaration.children[2].token.lexeme, "Integer"); // Data Type
    EXPECT_EQ(declaration.children[3].token.lexeme, "5"); // Array Size
}

// Test parsing assignments
TEST(ParserTest, ParseAssignment) {
    string input = "Assign x = 5";
    auto tokens = tokenizeInput(input);
    Parser parser(tokens);

    Node ast = parser.parse();
    ASSERT_EQ(ast.children.size(), 1);
    Node assignment = ast.children[0];

    EXPECT_EQ(assignment.type, NodeType::ASSIGNMENT);
    ASSERT_EQ(assignment.children.size(), 3); // Identifier, Operator, Expression
    EXPECT_EQ(assignment.children[0].token.lexeme, "x"); // Identifier
    EXPECT_EQ(assignment.children[1].token.lexeme, "="); // Operator
    EXPECT_EQ(assignment.children[2].children[0].token.lexeme, "5"); // Expression
}

// Test parsing print statements
TEST(ParserTest, ParsePrint) {
    string input = "Print \"Hello\"";
    auto tokens = tokenizeInput(input);
    Parser parser(tokens);

    Node ast = parser.parse();
    ASSERT_EQ(ast.children.size(), 1);
    Node printNode = ast.children[0];

    EXPECT_EQ(printNode.type, NodeType::PRINT);
    ASSERT_EQ(printNode.children.size(), 1); // String or Expression
    EXPECT_EQ(printNode.children[0].token.lexeme, "Hello"); // String
}

// Test parsing if statements
TEST(ParserTest, ParseIfStatement) {
    string input = R"(
        If x > 0 Then
            Print "Positive"
        Else
            Print "Negative"
        End If
    )";
    auto tokens = tokenizeInput(input);
    Parser parser(tokens);

    Node ast = parser.parse();
    ASSERT_EQ(ast.children.size(), 1);
    Node ifNode = ast.children[0];

    EXPECT_EQ(ifNode.type, NodeType::IF_STATEMENT);
    ASSERT_EQ(ifNode.children.size(), 3); // Condition, If Block, Else Block

    // Check the condition
    Node condition = ifNode.children[0];
    EXPECT_EQ(condition.children[0].token.lexeme, "x");
    EXPECT_EQ(condition.children[1].token.lexeme, ">");
    EXPECT_EQ(condition.children[2].token.lexeme, "0");

    // Check the if block
    Node ifBlock = ifNode.children[1];
    ASSERT_EQ(ifBlock.children.size(), 1);
    EXPECT_EQ(ifBlock.children[0].children[0].token.lexeme, "Positive"); // Print "Positive"

    // Check the else block
    Node elseBlock = ifNode.children[2];
    ASSERT_EQ(elseBlock.children.size(), 1);
    EXPECT_EQ(elseBlock.children[0].children[0].token.lexeme, "Negative"); // Print "Negative"
}

// Test parsing for loops
TEST(ParserTest, ParseForLoop) {
    string input = R"(
        For i = 0 To 5 Do
            Assign x = i * 2
        End For
    )";
    auto tokens = tokenizeInput(input);
    Parser parser(tokens);

    Node ast = parser.parse();
    ASSERT_EQ(ast.children.size(), 1);
    Node forNode = ast.children[0];

    EXPECT_EQ(forNode.type, NodeType::FOR_LOOP);
    ASSERT_EQ(forNode.children.size(), 3); // Start Condition, End Condition, For Block

    // Check start condition
    Node startCondition = forNode.children[0];
    EXPECT_EQ(startCondition.children[0].token.lexeme, "i");
    EXPECT_EQ(startCondition.children[1].token.lexeme, "=");
    EXPECT_EQ(startCondition.children[2].token.lexeme, "0");

    // Check end condition
    Node endCondition = forNode.children[1];
    EXPECT_EQ(endCondition.children[0].token.lexeme, "5");

    // Check the for block
    Node forBlock = forNode.children[2];
    ASSERT_EQ(forBlock.children.size(), 1);
    EXPECT_EQ(forBlock.children[0].type, NodeType::ASSIGNMENT);
}

// Test parsing while loops
TEST(ParserTest, ParseWhileLoop) {
    string input = R"(
        While x < 10 Do
            Print x
        End While
    )";
    auto tokens = tokenizeInput(input);
    Parser parser(tokens);

    Node ast = parser.parse();
    ASSERT_EQ(ast.children.size(), 1);
    Node whileNode = ast.children[0];

    EXPECT_EQ(whileNode.type, NodeType::WHILE_LOOP);
    ASSERT_EQ(whileNode.children.size(), 2); // Condition, While Block

    // Check the condition
    Node condition = whileNode.children[0];
    EXPECT_EQ(condition.children[0].token.lexeme, "x");
    EXPECT_EQ(condition.children[1].token.lexeme, "<");
    EXPECT_EQ(condition.children[2].token.lexeme, "10");

    // Check the while block
    Node whileBlock = whileNode.children[1];
    ASSERT_EQ(whileBlock.children.size(), 1);
    EXPECT_EQ(whileBlock.children[0].children[0].token.lexeme, "x"); // Print x
}
