#include <iostream>
#include <string>
using namespace std;

bool endsWith01(const string &s)
{
    // States:
    // q0 = 0, q1 = 1, q2 = 2, q3 = 3
    int state = 0;

    for (char ch : s)
    {
        switch (state)
        {
        case 0:
            if (ch == '0')
                state = 1;
            else if (ch == '1')
                state = 2;
            break;

        case 1:
            if (ch == '0')
                state = 1;
            else if (ch == '1')
                state = 3;
            break;

        case 2:
            if (ch == '0')
                state = 1;
            else if (ch == '1')
                state = 2;
            break;

        case 3:
            if (ch == '0')
                state = 1;
            else if (ch == '1')
                state = 2;
            break;
        }
    }

    // Accept if in state q3 (ends with 01)
    return (state == 3);
}

int main()
{
    string input;
    cout << "Enter a binary string: ";
    cin >> input;


    for (char c : input)
    {
        if (c != '0' && c != '1')
        {
            cout << "Invalid input!\n";
            return 1;
        }
    }

    if (endsWith01(input))
        cout << "Accepted.\n";
    else
        cout << "Rejected.\n";

    return 0;
}
