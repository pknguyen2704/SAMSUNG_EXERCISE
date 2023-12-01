#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool hasEulerCycle() {
        for (int i = 0; i < V; ++i) {
            if (adj[i].size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool isBridge(int u, int v) {
        int count1 = count(adj[u].begin(), adj[u].end(), v);
        int count2 = count(adj[v].begin(), adj[v].end(), u);
        return (count1 == 1 && count2 == 1);
    }

    bool isConnected() {
        vector<bool> visited(V, false);
        DFS(0, visited);

        for (bool vertexVisited : visited) {
            if (!vertexVisited) {
                return false;
            }
        }
        return true;
    }

    void DFS(int start, vector<bool>& visited) {
        stack<int> s;
        s.push(start);

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (!visited[current]) {
                visited[current] = true;
                for (int neighbor : adj[current]) {
                    if (!visited[neighbor]) {
                        s.push(neighbor);
                    }
                }
            }
        }
    }

    bool hasHamiltonCycle() {
        return isConnected() && !hasBridge();
    }

    bool hasBridge() {
        for (int u = 0; u < V; ++u) {
            for (int v : adj[u]) {
                if (isBridge(u, v)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    Graph g1(10); // Đồ thị 1
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(0, 3);
    g1.addEdge(1, 3);
    g1.addEdge(1, 4);
    g1.addEdge(2, 5);
    g1.addEdge(2, 9);
    g1.addEdge(3, 6);
    g1.addEdge(4, 7);
    g1.addEdge(4, 8);
    g1.addEdge(5, 8);
    g1.addEdge(5, 9);
    g1.addEdge(6, 7);
    g1.addEdge(6, 9);
    g1.addEdge(7, 8);

    Graph g2(10); // Đồ thị 2
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(0, 3);
    g2.addEdge(1, 3);
    g2.addEdge(0, 3);
    g2.addEdge(2, 5);
    g2.addEdge(5, 6);
    g2.addEdge(3, 6);
    g2.addEdge(4, 7);
    g2.addEdge(4, 8);
    g2.addEdge(5, 8);
    g2.addEdge(5, 9);
    g2.addEdge(6, 7);
    g2.addEdge(6, 9);
    g2.addEdge(8, 8);

    Graph g3(10); // Đồ thị 3
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(1, 3);
    g3.addEdge(0, 3);
    g3.addEdge(0, 4);
    g3.addEdge(2, 5);
    g3.addEdge(2, 9);
    g3.addEdge(3, 6);
    g3.addEdge(4, 7);
    g3.addEdge(4, 8);
    g3.addEdge(5, 8);
    g3.addEdge(5, 9);
    g3.addEdge(6, 7);
    g3.addEdge(6, 9);
    g3.addEdge(7, 8);

    Graph g4(10); // Đồ thị 4
    g4.addEdge(4, 1);
    g4.addEdge(7, 9);
    g4.addEdge(6, 2);
    g4.addEdge(7, 3);
    g4.addEdge(5, 0);
    g4.addEdge(0, 2);
    g4.addEdge(0, 8);
    g4.addEdge(1, 6);
    g4.addEdge(3, 9);
    g4.addEdge(6, 3);
    g4.addEdge(2, 8);
    g4.addEdge(1, 5);
    g4.addEdge(9, 8);
    g4.addEdge(4, 5);
    g4.addEdge(4, 7);

    cout << "Graph 1 has Euler Cycle: " << (g1.hasEulerCycle() ? "Yes" : "No") << endl;
    cout << "Graph 1 has Hamilton Cycle: " << (g1.hasHamiltonCycle() ? "Yes" : "No") << endl;

    cout << "Graph 2 has Euler Cycle: " << (g2.hasEulerCycle() ? "Yes" : "No") << endl;
    cout << "Graph 2 has Hamilton Cycle: " << (g2.hasHamiltonCycle() ? "Yes" : "No") << endl;

    cout << "Graph 3 has Euler Cycle: " << (g3.hasEulerCycle() ? "Yes" : "No") << endl;
    cout << "Graph 3 has Hamilton Cycle: " << (g3.hasHamiltonCycle() ? "Yes" : "No") << endl;

    cout << "Graph 4 has Euler Cycle: " << (g4.hasEulerCycle() ? "Yes" : "No") << endl;
    cout << "Graph 4 has Hamilton Cycle: " << (g4.hasHamiltonCycle() ? "Yes" : "No") << endl;

    return 0;
}
