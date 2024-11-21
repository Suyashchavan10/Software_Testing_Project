#include "../../src/codeGenerator/codeGenerator.h" // Header for the CodeGenerator class
#include "../../src/parser/parser.h" // Header for the Parser class
#include <gtest/gtest.h> // GoogleTest header
using namespace std;

// Helper function to tokenize and parse pseudocode
Node parseInput(const string& input) {
    Tokenizer tokenizer(input);
    auto tokens = tokenizer.tokenize();
    Parser parser(tokens);
    return parser.parse();
}

// Normalize whitespace in both strings
string normalizeWhitespace(const string& str) {
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
}

// Test code generation for variable declarations
TEST(CodeGeneratorTest, GenerateDeclaration) {
    string input = "Declare x As Integer";
    Node ast = parseInput(input);

    CodeGenerator generator;
    string generatedCode = generator.generateCode(ast);

    string expectedCode = R"(
        #include <bits/stdc++.h>
        using namespace std;

        int main() {

            int x;

            return 0;
        }
    )";
    EXPECT_EQ(normalizeWhitespace(generatedCode), normalizeWhitespace(expectedCode));
}

// Test code generation for array declarations
TEST(CodeGeneratorTest, GenerateArrayDeclaration) {
    string input = "Declare arr As Array Of Integer[5]";
    Node ast = parseInput(input);

    CodeGenerator generator;
    string generatedCode = generator.generateCode(ast);

    string expectedCode = R"(
        #include <bits/stdc++.h>
        using namespace std;

        int main() {

            int arr[5];

            return 0;
        }
    )";
    EXPECT_EQ(normalizeWhitespace(generatedCode), normalizeWhitespace(expectedCode));
}

// Test code generation for assignments
TEST(CodeGeneratorTest, GenerateAssignment) {
    string input = "Assign x = 5";
    Node ast = parseInput(input);

    CodeGenerator generator;
    string generatedCode = generator.generateCode(ast);

    string expectedCode = R"(
        #include <bits/stdc++.h>
        using namespace std;

        int main() {

            x = 5 ;

            return 0;
        }
    )";
    EXPECT_EQ(normalizeWhitespace(generatedCode), normalizeWhitespace(expectedCode));
}

// Test code generation for print statements
TEST(CodeGeneratorTest, GeneratePrintStatement) {
    string input = "Print \"Hello, World!\"";
    Node ast = parseInput(input);

    CodeGenerator generator;
    string generatedCode = generator.generateCode(ast);

    string expectedCode = R"(
        #include <bits/stdc++.h>
        using namespace std;

        int main() {

            cout << "Hello, World!" << endl;

            return 0;
        }
    )";
    EXPECT_EQ(normalizeWhitespace(generatedCode), normalizeWhitespace(expectedCode));
}

// Test code generation for if-else statements
TEST(CodeGeneratorTest, GenerateIfElse) {
    string input = R"(
        If x > 0 Then
            Print "Positive"
        Else
            Print "Negative"
        End If
    )";
    Node ast = parseInput(input);

    CodeGenerator generator;
    string generatedCode = generator.generateCode(ast);

    string expectedCode = R"(
        #include <bits/stdc++.h>
        using namespace std;

        int main() {

            if ( x > 0 ) {
                cout << "Positive" << endl;
            }
            else {
                cout << "Negative" << endl;
            }


            return 0;
        }
    )";
    EXPECT_EQ(normalizeWhitespace(generatedCode), normalizeWhitespace(expectedCode));
}

// Test code generation for for loops
TEST(CodeGeneratorTest, GenerateForLoop) {
    string input = R"(
        For i = 0 To 5 Do
            Assign x = i * 2
        End For
    )";
    Node ast = parseInput(input);

    CodeGenerator generator;
    string generatedCode = generator.generateCode(ast);

    string expectedCode = R"(
        #include <bits/stdc++.h>
        using namespace std;

        int main() {

            for (int i = 0 ; i <= 5 ; i++) {
                x = i * 2 ;
            }


            return 0;
        }
    )";
    EXPECT_EQ(normalizeWhitespace(generatedCode), normalizeWhitespace(expectedCode));
}

// Test code generation for while loops
TEST(CodeGeneratorTest, GenerateWhileLoop) {
    string input = R"(
        While x < 10 Do
            Print x
        End While
    )";
    Node ast = parseInput(input);

    CodeGenerator generator;
    string generatedCode = generator.generateCode(ast);

    string expectedCode = R"(
        #include <bits/stdc++.h>
        using namespace std;

        int main() {

            while (x < 10 ) {
                cout << x << endl;
            }


            return 0;
        }
    )";
    EXPECT_EQ(normalizeWhitespace(generatedCode), normalizeWhitespace(expectedCode));
}

