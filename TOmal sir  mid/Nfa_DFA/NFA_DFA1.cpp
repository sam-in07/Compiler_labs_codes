#include <iostream>
#include <string>
using namespace std;

// DFA that represents the NFA converted to DFA
// States: 0 = {A}, 1 = {A,B}, 2 = {A,B,C}
// Final state: 2

int transition(int state, char input) {
    switch (state) {
        case 0: // {A}
            if (input == '0') return 1; // {A,B}
            else if (input == '1') return 0; // {A}
            break;

        case 1: // {A,B}
            if (input == '0') return 2; // {A,B,C}
            else if (input == '1') return 1; // {A,B}
            break;

        case 2: // {A,B,C}
            if (input == '0' || input == '1') return 2; // stays {A,B,C}
            break;
    }
    return -1; // invalid input
}

bool dfaAccepts(const string &s) {
    int state = 0; // start state = {A}

    for (char c : s) {
        if (c != '0' && c != '1') {
            cout << "Invalid character: " << c << endl;
            return false;
        }
        state = transition(state, c);
        if (state == -1) return false;
    }

    // Accepting state is 2 ({A,B,C})
    return (state == 2);
}

int main() {
    string input;
    cout << "Enter a binary string: ";
    cin >> input;

    if (dfaAccepts(input))
        cout << "Accepted ✅ (Reached {A,B,C})" << endl;
    else
        cout << "Rejected ❌" << endl;

    return 0;
}
