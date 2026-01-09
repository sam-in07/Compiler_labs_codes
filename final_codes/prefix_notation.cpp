#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

// Function to return precedence
int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

// Convert infix to postfix
string infixToPostfix(string infix) {
    stack<char> st;
    string postfix = "";

    for (char c : infix) {
        // Operand
        if (isalnum(c)) {
            postfix += c;
        }
        // Left parenthesis
        else if (c == '(') {
            st.push(c);
        }
        // Right parenthesis
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop(); // remove '('
        }
        // Operator
        else {
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // Pop remaining operators
    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

int main() {
    string infix;
    cout << "Enter Infix Expression: ";
    cin >> infix;

    cout << "Postfix Expression: " << infixToPostfix(infix) << endl;
    return 0;
}
/*
input : a+(b*c+b*c+d)
Output : Enter Infix Expression: Postfix Expression: abc*bc*+d++

*/
