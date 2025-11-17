#include <iostream>
#include <string>
#include <unordered_set>
#include <cctype>
using namespace std;

// Set of C/C++ keywords
unordered_set<string> keywords = {
    "int", "float", "double", "char", "if", "else", "for", "while", "do",
    "switch", "case", "break", "continue", "return", "void", "long", "short",
    "unsigned", "signed", "bool", "const", "static"};

// Check if a string is a valid identifier
bool isIdentifier(const string &s)
{
    if (s.empty())
        return false;
    if (!isalpha(s[0]) && s[0] != '_')
        return false; // first char must be letter or _
    for (char c : s)
    {
        if (!isalnum(c) && c != '_')
            return false; // only letters, digits, _
    }
    return true;
}

int main()
{
    string line;
    string program = "";

    cout << "Enter the C/C++ program (end input with a single line containing END):\n";
    while (true)
    {
        getline(cin, line);
        if (line == "END")
            break;
        program += line + " ";
    }

    int identifierCount = 0;
    string token = "";

    for (size_t i = 0; i < program.length(); i++)
    {
        char c = program[i];

        // Token separators: space or punctuation/operators
        if (isspace(c) || ispunct(c))
        {
            if (!token.empty())
            {
                if (isIdentifier(token) && !keywords.count(token))
                {
                    identifierCount++;
                }
                token.clear();
            }
        }
        else
        {
            token += c;
        }
    }
    // Last token
    if (!token.empty() && isIdentifier(token) && !keywords.count(token))
    {
        identifierCount++;
    }

    cout << "Total number of identifiers: " << identifierCount << endl;

    return 0;
}
