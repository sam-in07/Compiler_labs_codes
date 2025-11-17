#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

// NFA transitions: state -> input char -> set of next states
map<int, map<char, set<int>>> trans;

// Epsilon transitions: state -> set of next states
map<int, set<int>> eps;

// Compute epsilon-closure of a set of states
set<int> epsilonClosure(const set<int> &states)
{
    set<int> closure = states;
    bool added = true;

    while (added)
    {
        added = false;
        for (int s : closure)
        {
            for (int nxt : eps[s])
            {
                if (!closure.count(nxt))
                {
                    closure.insert(nxt);
                    added = true;
                }
            }
        }
    }
    return closure;
}

// Simulate NFA
bool simulateNFA(const string &input)
{
    set<int> current = epsilonClosure({0}); // start state S0

    for (char c : input)
    {
        set<int> nextStates;

        for (int s : current)
        {
            if (trans[s].count(c))
            {
                for (int nxt : trans[s][c])
                    nextStates.insert(nxt);
            }
        }

        current = epsilonClosure(nextStates);
        if (current.empty())
            return false;
    }

    // Final accepting NFA state is 13 (F0)
    return current.count(13);
}

int main()
{
    // ------------------------------
    // Thompson NFA for a* | b(a|b)
    // States: 0..13
    // ------------------------------

    // a* NFA
    eps[0] = {1, 7};     // S0 -> S1(a*) and F0
    eps[1] = {2, 6};     // S1 -> q1 (a*) and F1
    trans[2]['a'] = {3}; // q1 --a--> q2
    eps[3] = {2, 6};     // q2 --ε--> q1 and F1
    eps[6] = {13};       // F1 --ε--> F0

    // b(a|b) NFA
    trans[4]['b'] = {5};   // q7 --b--> q8
    eps[5] = {8};          // q8 --ε--> s2 (union)
    eps[8] = {9, 11};      // s2 -> q3 (a) and q5 (b)
    trans[9]['a'] = {10};  // q3 --a--> q4
    eps[10] = {12};        // q4 --ε--> F2
    trans[11]['b'] = {12}; // q5 --b--> q6
    eps[12] = {13};        // F2 --ε--> F0

    string s;
    cout << "Enter a string over {a,b}: ";
    cin >> s;

    if (simulateNFA(s))
        cout << "Accepted ✅" << endl;
    else
        cout << "Rejected ❌" << endl;

    return 0;
}

/*
✅ Accepted Examples

"a" → Accepted (a* branch)

"aa" → Accepted (a* branch)

"b" → Rejected (must have b(a|b) → needs 2 chars)

"ba" → Accepted (b(a|b) branch)

"bb" → Accepted (b(a|b) branch)

❌ Rejected Examples

"" → Rejected

"c" → Rejected

"ab" → Rejected







*/