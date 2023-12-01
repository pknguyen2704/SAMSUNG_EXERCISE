#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V;
    vector<list<int>> adj;

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void DFS(int v, vector<bool>& visited, stack<int>& path) {
        visited[v] = true;

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFS(neighbor, visited, path);
            }
        }

        path.push(v);
    }

    bool isEulerianCycleExists() {
        vector<bool> visited(V, false);
        stack<int> path;

        int start_vertex = -1;
        for (int i = 0; i < V; ++i) {
            if (!adj[i].empty()) {
                start_vertex = i;
                break;
            }
        }

        if (start_vertex == -1) {
            return false;
        }

        DFS(start_vertex, visited, path);

        for (int i = 0; i < V; ++i) {
            if (!visited[i] && !adj[i].empty()) {
                return false;
            }
        }

        vector<int> in_degree(V, 0);
        vector<int> out_degree(V, 0);

        for (int i = 0; i < V; ++i) {
            out_degree[i] = adj[i].size();
            for (int neighbor : adj[i]) {
                in_degree[neighbor]++;
            }
        }

        for (int i = 0; i < V; ++i) {
            if (in_degree[i] != out_degree[i]) {
                return false;
            }
        }

        return true;
    }

    void findEulerianCycle() {
        if (!isEulerianCycleExists()) {
            cout << "Khong ton tai chu trinh Euler.\n";
            return;
        }

        vector<bool> visited(V, false);
        stack<int> path;

        int start_vertex = -1;
        for (int i = 0; i < V; ++i) {
            if (!adj[i].empty()) {
                start_vertex = i;
                break;
            }
        }

        DFS(start_vertex, visited, path);

        while (!path.empty()) {
            cout << path.top() << " ";
            path.pop();
        }
        cout << endl;
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 1);

    g.findEulerianCycle();

    return 0;
}
