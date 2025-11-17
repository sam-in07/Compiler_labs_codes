#include <iostream>
#include <string>
using namespace std;


bool noConsecutiveB(const string &s) {
    // States: q0 = 0, q1 = 1, q2 = 2 (trap)
    int state = 0;

    for (char ch : s) {
        switch (state) {
            case 0: // q0
                if (ch == 'a') state = 0;
                else if (ch == 'b') state = 1;
                else return false; // invalid input
                break;

            case 1: // q1 (last was b)
                if (ch == 'a') state = 0;
                else if (ch == 'b') state = 2; // two b's in a row
                else return false;
                break;

            case 2: // trap
                state = 2;
                break;
        }
    }

    // Accepting states: q0, q1
    return (state == 0 || state == 1);
}

int main() {
    string input;
    cout << "Enter a string over {a,b}: ";
    cin >> input;

    if (noConsecutiveB(input))
        cout << "Accepted: No consecutive b's.\n";
    else
        cout << "Rejected: Contains consecutive b's.\n";

    return 0;
}
