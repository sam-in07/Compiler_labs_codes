#include <iostream>
#include <string>
using namespace std;

// DFA for regex (a|b)*abb
// States:
// 0 = no match yet
// 1 = matched 'a'
// 2 = matched 'ab'
// 3 = matched 'abb' (final state)

int transition(int state, char input)
{
    switch (state)
    {
    case 0:
        if (input == 'a')
            return 1;
        if (input == 'b')
            return 0;
        break;

    case 1:
        if (input == 'a')
            return 1;
        if (input == 'b')
            return 2;
        break;

    case 2:
        if (input == 'a')
            return 1;
        if (input == 'b')
            return 3;
        break;

    case 3: // already matched "abb"
        if (input == 'a')
            return 1;
        if (input == 'b')
            return 0;
        break;
    }
    return -1; // invalid input
}

bool dfaAccepts(const string &s)
{
    int state = 0; // start state

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

    // Accept if in state 3
    return (state == 3);
}

int main()
{
    string input;
    cout << "Enter a string over {a,b}: ";
    cin >> input;

    if (dfaAccepts(input))
        cout << "Accepted ✅ (matched ending 'abb')" << endl;
    else
        cout << "Rejected ❌" << endl;

    return 0;
}

/*
Input: abb
→ Accepted

Input: aabb
→ Accepted

Input: bababb
→ Accepted

Input: abba
→ Rejected



*/