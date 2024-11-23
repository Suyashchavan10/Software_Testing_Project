#include "../../src/parser/parser.cpp"
#include "../../src/tokenizer/tokenizer.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Helper function to validate a node in the AST
bool checkNode(const Node& node, NodeType expectedType, const string& expectedLexeme) {
    return node.type == expectedType && node.token.lexeme == expectedLexeme;
}

// Helper function to parse input pseudocode and return the AST
Node parseInput(const string& pseudocode) {
    Tokenizer tokenizer(pseudocode);
    vector<Token> tokens = tokenizer.tokenize();
    Parser parser(tokens);
    return parser.parse();
}

int main() {
    // Test Case 1: Parse variable declaration
    {
        string input = "Declare x As Integer";
        Node ast = parseInput(input);

        if (ast.children.size() != 1 || 
            !checkNode(ast.children[0], NodeType::DECLARATION, "Declare") ||
            ast.children[0].children.size() != 2 || 
            !checkNode(ast.children[0].children[0], NodeType::IDENTIFIER, "x") ||
            !checkNode(ast.children[0].children[1], NodeType::IDENTIFIER, "Integer")) {
            return 1; // Test failed
        }
    }

    // Test Case 2: Parse assignment
    {
        string input = "Assign x = 5";
        Node ast = parseInput(input);

        if (ast.children.size() != 1 || 
            !checkNode(ast.children[0], NodeType::ASSIGNMENT, "Assign") ||
            ast.children[0].children.size() != 3 || 
            !checkNode(ast.children[0].children[0], NodeType::IDENTIFIER, "x") ||
            !checkNode(ast.children[0].children[1], NodeType::IDENTIFIER, "=") ||
            !checkNode(ast.children[0].children[2].children[0], NodeType::IDENTIFIER, "5")) {
            return 1; // Test failed
        }
    }

    // Test Case 3: Parse print statement
    {
        string input = "Print \"Hello, World!\"";
        Node ast = parseInput(input);

        if (ast.children.size() != 1 || 
            !checkNode(ast.children[0], NodeType::PRINT, "Print") ||
            ast.children[0].children.size() != 1 || 
            !checkNode(ast.children[0].children[0], NodeType::IDENTIFIER, "Hello, World!")) {
            return 1; // Test failed
        }
    }

    // Test Case 4: Parse if-else statement
    {
        string input = R"(
            If x > 0 Then
                Print "Positive"
            Else
                Print "Negative"
            End If
        )";
        Node ast = parseInput(input);

        if (ast.children.size() != 1 || 
            !checkNode(ast.children[0], NodeType::IF_STATEMENT, "If") ||
            ast.children[0].children.size() != 3 || 
            !checkNode(ast.children[0].children[0], NodeType::EXPRESSION, "") || // Condition
            !checkNode(ast.children[0].children[1], NodeType::BLOCK, "Then") || // If block
            !checkNode(ast.children[0].children[2], NodeType::BLOCK, "Else")) { // Else block
            return 1; // Test failed
        }
    }

    // Test Case 5: Parse for loop
    {
        string input = R"(
            For i = 0 To 5 Do
                Print i
            End For
        )";
        Node ast = parseInput(input);

        if (ast.children.size() != 1 || 
            !checkNode(ast.children[0], NodeType::FOR_LOOP, "For") ||
            ast.children[0].children.size() != 3 || 
            !checkNode(ast.children[0].children[0], NodeType::EXPRESSION, "") || // Start condition
            !checkNode(ast.children[0].children[1], NodeType::EXPRESSION, "") || // End condition
            !checkNode(ast.children[0].children[2], NodeType::BLOCK, "Do")) { // Loop block
            return 1; // Test failed
        }
    }

    // Test Case 6: Parse while loop
    {
        string input = R"(
            While x < 10 Do
                Print x
            End While
        )";
        Node ast = parseInput(input);

        if (ast.children.size() != 1 || 
            !checkNode(ast.children[0], NodeType::WHILE_LOOP, "While") ||
            ast.children[0].children.size() != 2 || 
            !checkNode(ast.children[0].children[0], NodeType::EXPRESSION, "") || // Condition
            !checkNode(ast.children[0].children[1], NodeType::BLOCK, "Do")) { // Loop block
            return 1; // Test failed
        }
    }

    // Test Case 7: Parse array declaration
    {
        string input = "Declare arr As Array Of Integer[5]";
        Node ast = parseInput(input);

        if (ast.children.size() != 1 || 
            !checkNode(ast.children[0], NodeType::DECLARATION, "Declare") ||
            ast.children[0].children.size() != 4 || 
            !checkNode(ast.children[0].children[0], NodeType::IDENTIFIER, "arr") ||
            !checkNode(ast.children[0].children[1], NodeType::IDENTIFIER, "Array") ||
            !checkNode(ast.children[0].children[2], NodeType::IDENTIFIER, "Integer") ||
            !checkNode(ast.children[0].children[3], NodeType::IDENTIFIER, "5")) {
            return 1; // Test failed
        }
    }

    // Test Case 8: Check string tokenization
    {
        string input = "Declare str As String";
        Node ast = parseInput(input);

        if (ast.children.size() != 1 || 
            !checkNode(ast.children[0], NodeType::DECLARATION, "Declare") ||
            ast.children[0].children.size() != 2 || 
            !checkNode(ast.children[0].children[0], NodeType::IDENTIFIER, "str") ||
            !checkNode(ast.children[0].children[1], NodeType::IDENTIFIER, "String")) {
            return 1; // Test failed
        }

    }

    // Test Case 9: Test loop boundary conditions
    {
        string input = R"(
            For i = 0 To 5 Do
                Print i
            End For
        )";
        Node ast = parseInput(input);

        // Check if the AST correctly processes all iterations
        if (ast.children.size() != 1 || 
            !checkNode(ast.children[0], NodeType::FOR_LOOP, "For") ||
            ast.children[0].children[2].children.size() != 6) { // Should cover 6 iterations
            return 1; // Test failed
        }
    }

    // Test Case 10: Nested conditionals and boundary conditions
    {
        string input = R"(
            If x > 0 Then
                If x < 10 Then
                    Print "Valid"
                Else
                    Print "Invalid"
                End If
            Else
                Print "Negative"
            End If
        )";
        Node ast = parseInput(input);

        // Ensure both If and Else blocks are processed
        if (ast.children.size() != 1 || 
            ast.children[0].children.size() != 3 || // Condition, If block, Else block
            !checkNode(ast.children[0].children[1], NodeType::BLOCK, "Then") ||
            !checkNode(ast.children[0].children[2], NodeType::BLOCK, "Else")) {
            return 1; // Test failed
        }
    }

    // All tests passed
    return 0;
}
