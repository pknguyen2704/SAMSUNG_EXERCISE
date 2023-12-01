#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

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

    void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& order) {
        visited[v] = true;
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                topologicalSortUtil(neighbor, visited, order);
            }
        }
        order.push(v);
    }

    bool hasHamiltonianPath() {
        stack<int> order;
        vector<bool> visited(V, false);
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, order);
            }
        }

        unordered_set<int> seenVertices;
        int prevVertex = -1;

        while (!order.empty()) {
            int currentVertex = order.top();
            order.pop();

            if (seenVertices.find(currentVertex) != seenVertices.end()) {
                return false;
            }

            seenVertices.insert(currentVertex);

            if (prevVertex != -1) {
                bool hasEdge = false;
                for (int neighbor : adj[prevVertex]) {
                    if (neighbor == currentVertex) {
                        hasEdge = true;
                        break;
                    }
                }

                if (!hasEdge) {
                    return false;
                }
            }

            prevVertex = currentVertex;
        }

        return true;
    }
};

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 0);

    if (g.hasHamiltonianPath()) {
        cout << "Do thi co duong di Hamilton.\n";
    } else {
        cout << "Do thi khong co duong di Hamilton.\n";
    }

    return 0;
}
