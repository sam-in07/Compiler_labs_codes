#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct Quadruple {
    string op, arg1, arg2, result;
};

struct Triple {
    string op, arg1, arg2;
};

int main() {
    vector<Quadruple> quads;
    vector<Triple> triples;
    vector<string> tempVars;

    string line;
    cout << "Enter expressions line by line (empty line to stop):\n";

    while (true) {
        getline(cin, line);
        if (line.empty()) break; // stop on empty line

        string result, equalSign, arg1, op, arg2;

        stringstream ss(line);
        ss >> result >> equalSign >> arg1 >> op >> arg2;

        // Store in Quadruple
        Quadruple q = {op, arg1, arg2, result};
        quads.push_back(q);

        // For Triple: replace arg1/arg2 with index if it’s a temp variable
        for (int i = 0; i < tempVars.size(); i++) {
            if (arg1 == tempVars[i]) arg1 = "(" + to_string(i) + ")";
            if (arg2 == tempVars[i]) arg2 = "(" + to_string(i) + ")";
        }

        Triple t = {op, arg1, arg2};
        triples.push_back(t);

        // Add result to tempVars for future reference
        tempVars.push_back(result);
    }


    cout << "\nQUADRUPLES\n";
    cout << "Op\tArg1\tArg2\tResult\n";
    for (auto q : quads) {
        cout << q.op << "\t" << q.arg1 << "\t" << q.arg2 << "\t" << q.result << "\n";
    }


    cout << "\nTRIPLES\n";
    cout << "Index\tOp\tArg1\tArg2\n";
    for (int i = 0; i < triples.size(); i++) {
        cout << i << "\t" << triples[i].op << "\t" << triples[i].arg1 << "\t" << triples[i].arg2 << "\n";
    }

    return 0;
}
/*  
Input : 
T1 = b * c
T2 = T1 + T1
T3 = T2 + d
T4 = T3 + a

Output : 

Enter expressions line by line (empty line to stop):

QUADRUPLES
Op	Arg1	Arg2	Result
*	b	c	T1
+	T1	T1	T2
+	T2	d	T3
+	T3	a	T4

TRIPLES
Index	Op	Arg1	Arg2
0	*	b	c
1	+	(0)	(0)
2	+	(1)	d
3	+	(2)	a


*/
