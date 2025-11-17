#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

// NFA transitions: state -> input -> set of next states
map<int, map<char, set<int>>> transitions;

// Epsilon transitions: state -> set of next states
map<int, set<int>> epsilonTransitions;

// Compute epsilon-closure of a set of states
set<int> epsilonClosure(const set<int> &states)
{
    set<int> closure = states;
    bool changed = true;

    while (changed)
    {
        changed = false;
        set<int> newStates;

        for (int s : closure)
        {
            for (int nxt : epsilonTransitions[s])
            {
                if (!closure.count(nxt))
                {
                    newStates.insert(nxt);
                    changed = true;
                }
            }
        }
        closure.insert(newStates.begin(), newStates.end());
    }
    return closure;
}

bool simulateNFA(const string &input)
{
    // Start state is q0 → ε-closure(q0)
    set<int> currentStates = epsilonClosure({0});

    for (char c : input)
    {
        set<int> nextStates;

        for (int state : currentStates)
        {
            if (transitions[state].count(c))
            {
                for (int nxt : transitions[state][c])
                {
                    nextStates.insert(nxt);
                }
            }
        }

        currentStates = epsilonClosure(nextStates);
        if (currentStates.empty())
            return false;
    }

    // Accepting state is q3
    return currentStates.count(3) > 0;
}

int main()
{
    // Build NFA for a(b|c)*
    transitions[0]['a'] = {1};
    epsilonTransitions[1] = {2};
    transitions[2]['b'] = {2};
    transitions[2]['c'] = {2};
    epsilonTransitions[2] = {3};

    string s;
    cout << "Enter a string over {a,b,c}: ";
    cin >> s;

    if (simulateNFA(s))
        cout << "Accepted ✅" << endl;
    else
        cout << "Rejected ❌" << endl;

    return 0;
}

/*

So the valid strings are:

a
ab
ac
abbc
acccbbbccc
… etc.

Invalid examples:

""
b…
ca…
aa…
aX… (invalid char)









*/