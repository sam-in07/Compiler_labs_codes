#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>
using namespace std;

// Keywords
unordered_set<string> keywords = {"int", "float", "if", "else"};

// Single and multi-character operators
unordered_set<string> operators = {"+", "-", "*", "/", "=", "==", "!=", "<=", ">=", "<", ">"};

// Separators
unordered_set<char> separators = {';', ',', '(', ')', '{', '}'};

// Check if string is a keyword
bool isKeyword(const string &s)
{
    return keywords.count(s);
}

// Check if string is an operator
bool isOperator(const string &s)
{
    return operators.count(s);
}

// Check if char is part of operator (for multi-char operators)
bool isOperatorChar(char c)
{
    string opChars = "+-*/=<>!";
    return opChars.find(c) != string::npos;
}

// Check if string is a number (integer or float)
bool isNumber(const string &s)
{
    bool hasDecimal = false;
    if (s.empty())
        return false;
    for (size_t i = 0; i < s.size(); i++)
    {
        if (s[i] == '.')
        {
            if (hasDecimal)
                return false; // multiple decimals
            hasDecimal = true;
        }
        else if (!isdigit(s[i]))
            return false;
    }
    return true;
}

// Check if string is a valid identifier
bool isIdentifier(const string &s)
{
    if (s.empty())
        return false;
    if (!isalpha(s[0]) && s[0] != '_')
        return false;
    for (char c : s)
    {
        if (!isalnum(c) && c != '_')
            return false;
    }
    return true;
}

int main()
{
    string input;
    cout << "Enter input: ";
    getline(cin, input);

    vector<string> tokens;
    string token = "";
    size_t i = 0;

    while (i < input.length())
    {
        char c = input[i];

        if (isspace(c))
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            i++;
        }
        // Separators
        else if (separators.count(c))
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, c));
            i++;
        }
        // Operator (handle multi-character)
        else if (isOperatorChar(c))
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            string op(1, c);
            // Check for two-character operators
            if (i + 1 < input.length())
            {
                string twoCharOp = op + input[i + 1];
                if (isOperator(twoCharOp))
                {
                    op = twoCharOp;
                    i++;
                }
            }
            tokens.push_back(op);
            i++;
        }
        else
        {
            token += c;
            i++;
        }
    }
    if (!token.empty())
        tokens.push_back(token);

    // Classify tokens
    for (string t : tokens)
    {
        if (isKeyword(t))
            cout << t << " : Keyword" << endl;
        else if (isOperator(t))
            cout << t << " : Operator" << endl;
        else if (separators.count(t[0]))
            cout << t << " : Separator" << endl;
        else if (isNumber(t))
            cout << t << " : Number" << endl;
        else if (isIdentifier(t))
            cout << t << " : Identifier" << endl;
        else
            cout << t << " : Unknown" << endl;
    }

    return 0;
}
