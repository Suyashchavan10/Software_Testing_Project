#include "../../src/codeGenerator/codeGenerator.cpp"
#include "../../src/parser/parser.h"
#include "../../src/tokenizer/tokenizer.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Helper function to validate generated code
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
    // Test Case 1: Generate code for variable declaration
    {
        string input = "Declare x As Integer";
        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();
        Parser parser(tokens);
        Node ast = parser.parse();

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

        if (!checkGeneratedCode(generatedCode, expectedCode)) {
            cerr << "Test Case 1 Failed: Variable Declaration" << endl;
            return 1;
        }
    }

    // Test Case 2: Generate code for assignment
    {
        string input = "Assign x = 5";
        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();
        Parser parser(tokens);
        Node ast = parser.parse();

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

        if (!checkGeneratedCode(generatedCode, expectedCode)) {
            cerr << "Test Case 2 Failed: Assignment" << endl;
            return 1;
        }
    }

    // Test Case 3: Generate code for if-else statement
    {
        string input = R"(
            If x > 0 Then
                Print "Positive"
            Else
                Print "Negative"
            End If
        )";
        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();
        Parser parser(tokens);
        Node ast = parser.parse();

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

        if (!checkGeneratedCode(generatedCode, expectedCode)) {
            cerr << "Test Case 3 Failed: If-Else Statement" << endl;
            return 1;
        }
    }

    // Test Case 4: Generate code for for loop
    {
        string input = R"(
            For i = 0 To 5 Do
                Assign x = i * 2
            End For
        )";
        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();
        Parser parser(tokens);
        Node ast = parser.parse();

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

        if (!checkGeneratedCode(generatedCode, expectedCode)) {
            cerr << "Test Case 4 Failed: For Loop" << endl;
            return 1;
        }
    }

    // Test Case 5: Generate code for print statement
    {
        string input = R"(
            Print "Hello, World!"
        )";
        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();
        Parser parser(tokens);
        Node ast = parser.parse();

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

        if (!checkGeneratedCode(generatedCode, expectedCode)) {
            cerr << "Test Case 5 Failed: Print Statement" << endl;
            return 1;
        }
    }

    // Test Case 6: Declaration with 2D array and matrix
    {
        string input = R"(
            Declare matrix As Array Of Integer[3][3]
        )";
        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();
        Parser parser(tokens);
        Node ast = parser.parse();

        CodeGenerator generator;
        string generatedCode = generator.generateCode(ast);

        string expectedCode = R"(
            #include <bits/stdc++.h>
            using namespace std;

            int main() {

                int matrix[3][3];

                return 0;
            }
        )";

        if (!checkGeneratedCode(generatedCode, expectedCode)) {
            cerr << "Test Case Failed: 2D Array Declaration" << endl;
            return 1;
        }
    }

    // Test Case 7: For loop boundary conditions
    {
        string input = R"(
            For i = 0 To 5 Do
                Print i
            End For
        )";

        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();
        Parser parser(tokens);
        Node ast = parser.parse();

        CodeGenerator generator;
        string generatedCode = generator.generateCode(ast);

        string expectedCode = R"(
            #include <bits/stdc++.h>
            using namespace std;

            int main() {

                for (int i = 0 ; i <= 5 ; i++) {
                    cout << i << endl;
                }


                return 0;
            }
        )";

        if (!checkGeneratedCode(generatedCode, expectedCode)) {
            cerr << "Test Case Failed: For Loop Boundary Condition" << endl;
            return 1;
        }
    }

    // Test Case 8: Assignment within a conditional
    {
        string input = R"(
            If x == 0 Then
                Assign y = 5
            End If
        )";

        Tokenizer tokenizer(input);
        vector<Token> tokens = tokenizer.tokenize();
        Parser parser(tokens);
        Node ast = parser.parse();

        CodeGenerator generator;
        string generatedCode = generator.generateCode(ast);

        string expectedCode = R"(
            #include <bits/stdc++.h>
            using namespace std;

            int main() {

                if ( x == 0 ) {
                    y = 5 ;
                }


                return 0;
            }
        )";

        if (!checkGeneratedCode(generatedCode, expectedCode)) {
            cerr << "Test Case Failed: Equality in If Statement" << endl;
            return 1;
        }
    }


    // All tests passed
    cout << "All tests passed successfully!" << endl;
    return 0;
}
