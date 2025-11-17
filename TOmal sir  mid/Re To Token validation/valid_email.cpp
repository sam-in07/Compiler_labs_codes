#include <iostream>
#include <regex>
#include <string>
using namespace std;

bool isValidEmail(const string &email)
{
    // Simple regex for email validation
    string pattern = R"((\w+)(\.\w+)*@(\w+)\.(\w{2,6}))";
    regex re(pattern);
    return regex_match(email, re);
}

int main()
{
    string input;

    cout << "Enter emails to validate (type 'exit' to quit):" << endl;

    while (true)
    {
        cout << "> ";
        cin >> input;

        if (input == "exit")
            break;

        if (isValidEmail(input))
            cout << input << " : Valid Email ✅" << endl;
        else
            cout << input << " : Invalid Email ❌" << endl;
    }

    return 0;
}
