#include <iostream>
#include <vector>
#include <stack>

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
    }

    void DFS1(int v, vector<bool>& visited, stack<int>& resultStack) {
        visited[v] = true;
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFS1(neighbor, visited, resultStack);
            }
        }
        resultStack.push(v);
    }

    void DFS2(int v, vector<bool>& visited, vector<int>& scc) {
        visited[v] = true;
        scc.push_back(v);
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFS2(neighbor, visited, scc);
            }
        }
    }

    void stronglyConnectedComponents(int startVertex) {
        vector<bool> visited1(V, false);
        stack<int> resultStack;

        DFS1(startVertex, visited1, resultStack);

        vector<vector<int>> reversedGraph(V);
        for (int i = 0; i < V; ++i) {
            for (int neighbor : adj[i]) {
                reversedGraph[neighbor].push_back(i);
            }
        }

        vector<bool> visited2(V, false);
        while (!resultStack.empty()) {
            int currentVertex = resultStack.top();
            resultStack.pop();

            if (!visited2[currentVertex]) {
                vector<int> scc;
                DFS2(currentVertex, visited2, scc);
                for (int vertex : scc) {
                    cout << vertex << " ";
                }
                cout << endl;
            }
        }
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    int startVertex = 0;
    cout << startVertex << endl;
    g.stronglyConnectedComponents(startVertex);

    return 0;
}
