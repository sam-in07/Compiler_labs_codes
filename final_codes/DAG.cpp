#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class DAG {
private:
    unordered_map<int, vector<int>> adjList;
    unordered_map<int, int> inDegree;  // To track in-degrees of vertices

public:
    // Add a directed edge from u to v
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        inDegree[v]++;
        // Ensure all nodes are included in the inDegree map
        if (inDegree.find(u) == inDegree.end()) {
            inDegree[u] = 0;
        }
    }

    // Perform topological sorting using Kahn's Algorithm
    void topologicalSort() {
        queue<int> q;
        vector<int> topoOrder;

        // Find all nodes with no incoming edges (in-degree 0)
        for (auto node : inDegree) {
            if (node.second == 0) {
                q.push(node.first);
            }
        }

        // Process the nodes with in-degree 0
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            topoOrder.push_back(current);

            // Decrease in-degree of adjacent nodes and push those with in-degree 0
            for (int neighbor : adjList[current]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // If we processed all nodes, print the topological order
        if (topoOrder.size() == inDegree.size()) {
            cout << "Topological Sort: ";
            for (int node : topoOrder) {
                cout << node << " ";
            }
            cout << endl;
        } else {
            cout << "The graph has a cycle!" << endl;
        }
    }

    // Function to print the adjacency list
    void printGraph() {
        for (auto node : adjList) {
            cout << node.first << " -> ";
            for (int neighbor : node.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    DAG g;
    int numEdges;

    // Step 1: Read number of edges
    cout << "Enter number of edges: ";
    cin >> numEdges;

    // Step 2: Read the directed edges (u, v)
    cout << "Enter the edges (u v format):\n";
    for (int i = 0; i < numEdges; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    // Step 3: Print the graph (Adjacency List)
    cout << "Graph representation (Adjacency List):\n";
    g.printGraph();

    // Step 4: Perform topological sort
    g.topologicalSort();

    return 0;
}
/*
Enter number of edges: 6
Enter the edges (u v format):
5 2
5 0
4 0
4 1
2 3
3 1

Graph representation (Adjacency List):
5 -> 2 0 
4 -> 0 1 
2 -> 3 
3 -> 1 

Topological Sort: 5 4 2 3 1 0 


*/
