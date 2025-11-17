#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Function to check if a string is a valid integer
bool isValidInteger(const string &s)
{
    if (s.empty())
        return false;

    size_t i = 0;

    // Check optional negative sign
    if (s[0] == '-')
    {
        if (s.length() == 1)
            return false; // '-' alone is invalid
        i = 1;
    }

    // All remaining characters must be digits
    for (; i < s.length(); i++)
    {
        if (!isdigit(s[i]))
            return false;
    }

    return true;
}

int main()
{
    string input;

    cout << "Enter a string to check if it is a valid integer (type 'exit' to quit):" << endl;

    while (true)
    {
        cout << "> ";
        cin >> input;

        if (input == "exit")
            break;

        if (isValidInteger(input))
            cout << input << " : Valid Integer ✅" << endl;
        else
            cout << input << " : Invalid Integer ❌" << endl;
    }

    return 0;
}
