#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

// NFA transitions: state -> (input char -> next states)
map<int, map<char, set<int>>> trans;

// Epsilon transitions: state -> next states
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

    // Final accepting NFA state is 10
    return current.count(10);
}

int main()
{
    // ---------------------------------------------------------
    // NFA CONSTRUCTION for (ab + b)* a
    //
    // State numbers:
    // 0: S0 (new start)
    // 1: S
    // (ab)
    // 2: q0
    // 3: q1
    // 4: q2
    // (b)
    // 5: q3
    // 6: q4
    //
    // 7: F (end of union)
    // 8: F0 (end of star)
    // 10: Final state
    // ---------------------------------------------------------

    eps[0] = {1, 8}; // S0 -> S and F0
    eps[1] = {2, 5}; // S -> q0 (ab) and q3 (b)

    trans[2]['a'] = {3}; // q0 --a--> q1
    trans[3]['b'] = {4}; // q1 --b--> q2
    eps[4] = {7};        // q2 --ε--> F

    trans[5]['b'] = {6}; // q3 --b--> q4
    eps[6] = {7};        // q4 --ε--> F

    eps[7] = {1, 8};      // F loops back to S, or goes to F0
    trans[8]['a'] = {10}; // F0 --a--> final state (10)

    // ---------------------------------------------------------
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
| Input     | Output   |
| --------- | -------- |
| `a`       | Accepted |
| `ba`      | Accepted |
| `aba`     | Accepted |
| `bba`     | Accepted |
| `abbba`   | Accepted |
| `ababbba` | Accepted |
| `""`      | Rejected |
| `ab`      | Rejected |
| `bbb`     | Rejected |







*/