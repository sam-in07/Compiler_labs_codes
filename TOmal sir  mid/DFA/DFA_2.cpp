#include <iostream>
#include <string>
using namespace std;

// Function to check if a binary string has an even number of 1s
bool hasEvenOnes(const string& str) {
    // Start in the "even" state (true = even, false = odd)
    bool isEven = true;

    for (char ch : str) {
        if (ch == '1') {
            // Flip state on every '1'
            isEven = !isEven;
        } else if (ch != '0') {
            // Invalid character
            cout << "Invalid input: only 0 and 1 are allowed.\n";
            return false;
        }
    }

    // If we end in the even state, accept the string
    return isEven;
}

int main() {
    string input;
    cout << "Enter a binary string: ";
    cin >> input;

    if (hasEvenOnes(input)) {
        cout << "✅ Accepted (even number of 1s)\n";
    } else {
        cout << "❌ Rejected (odd number of 1s)\n";
    }

    return 0;
}
