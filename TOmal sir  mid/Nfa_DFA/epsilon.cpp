#include <iostream>
#include <string>
using namespace std;

// DFA states:
// 0 = {q0, q1} (start)
// 1 = {q1}
// 2 = {q2} (final)
// 3 = dead state ∅

int transition(int state, char input)
{
    switch (state)
    {

    case 0: // {q0, q1}
        if (input == 'a')
            return 1;
        if (input == 'b')
            return 2;
        break;

    case 1: // {q1}
        if (input == 'a')
            return 1;
        if (input == 'b')
            return 2;
        break;

    case 2: // {q2} (accept state)
        if (input == 'a')
            return 3;
        if (input == 'b')
            return 3;
        break;

    case 3: // dead state
        if (input == 'a' || input == 'b')
            return 3;
        break;
    }
    return -1; // invalid input
}

bool dfaAccepts(const string &s)
{
    int state = 0; // start at {q0, q1}

    for (char c : s)
    {
        if (c != 'a' && c != 'b')
        {
            cout << "Invalid character: " << c << endl;
            return false;
        }
        state = transition(state, c);
        if (state == -1)
            return false;
    }

    // Accepting state is 2 ({q2})
    return (state == 2);
}

int main()
{
    string input;
    cout << "Enter a string over {a,b}: ";
    cin >> input;

    if (dfaAccepts(input))
        cout << "Accepted ✅" << endl;
    else
        cout << "Rejected ❌" << endl;

    return 0;
}

/*
| Input   | Result   |
| ------- | -------- |
| `b`     | Accepted |
| `ab`    | Accepted |
| `aaab`  | Accepted |
| `aabbb` | Rejected |




*/