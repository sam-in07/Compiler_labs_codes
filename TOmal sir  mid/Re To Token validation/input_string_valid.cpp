#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Function to check if a string is a valid identifier
bool isValidIdentifier(const string &s)
{
    if (s.empty())
        return false;

    // First character must be letter or underscore
    if (!isalpha(s[0]) && s[0] != '_')
        return false;

    // Remaining characters must be letters, digits, or underscore
    for (size_t i = 1; i < s.length(); i++)
    {
        if (!isalnum(s[i]) && s[i] != '_')
            return false;
    }

    return true;
}

int main()
{
    string input;
    cout << "Enter a string to check if it is a valid identifier: ";
    cin >> input;

    if (isValidIdentifier(input))
        cout << input << " : Valid Identifier ✅" << endl;
    else
        cout << input << " : Invalid Identifier ❌" << endl;

    return 0;
}
