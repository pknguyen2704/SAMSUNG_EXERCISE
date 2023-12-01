#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;
    int time;

    void bridgeDFS(int u, vector<int>& disc, vector<int>& low, vector<int>& parent) {
        disc[u] = low[u] = ++time;

        for (int v : adj[u]) {
            if (disc[v] == -1) {
                parent[v] = u;
                bridgeDFS(v, disc, low, parent);

                low[u] = min(low[u], low[v]);

                if (low[v] > disc[u]) {
                    cout << "Bridge: (" << u << "," << v << ")" << endl;
                }
            } else if (v != parent[u]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

public:
    Graph(int vertices) : V(vertices), time(0) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void findBridges() {
        vector<int> disc(V, -1);
        vector<int> low(V, -1);
        vector<int> parent(V, -1);

        cout << "Bridges in the graph:\n";
        for (int i = 0; i < V; ++i) {
            if (disc[i] == -1) {
                bridgeDFS(i, disc, low, parent);
            }
        }
    }
};

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 3);

    g.findBridges();

    return 0;
}
