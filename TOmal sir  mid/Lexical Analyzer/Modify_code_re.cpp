#include <iostream>
#include <string>
using namespace std;

// Function to remove comments
string removeComments(const string &code)
{
    string result = "";
    bool inSingleLineComment = false;
    bool inMultiLineComment = false;

    for (size_t i = 0; i < code.size(); i++)
    {
        if (inSingleLineComment)
        {
            if (code[i] == '\n')
            {
                inSingleLineComment = false;
                result += '\n';
            }
        }
        else if (inMultiLineComment)
        {
            if (code[i] == '*' && i + 1 < code.size() && code[i + 1] == '/')
            {
                inMultiLineComment = false;
                i++; // skip '/'
            }
        }
        else
        {
            // Check for start of single-line comment
            if (code[i] == '/' && i + 1 < code.size() && code[i + 1] == '/')
            {
                inSingleLineComment = true;
                i++; // skip second '/'
            }
            // Check for start of multi-line comment
            else if (code[i] == '/' && i + 1 < code.size() && code[i + 1] == '*')
            {
                inMultiLineComment = true;
                i++; // skip '*'
            }
            else
            {
                result += code[i];
            }
        }
    }

    return result;
}

int main()
{
    string line;
    string program = "";

    cout << "Enter C/C++ program (type END on a new line to finish):\n";
    while (true)
    {
        getline(cin, line);
        if (line == "END")
            break;
        program += line + "\n";
    }

    string cleanedCode = removeComments(program);

    cout << "\n--- Cleaned Code ---\n";
    cout << cleanedCode;

    return 0;
}
