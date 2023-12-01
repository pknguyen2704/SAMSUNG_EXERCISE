#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

struct Edge {
    int u, v, weight;
    Edge(int _u, int _v, int _weight) : u(_u), v(_v), weight(_weight) {}
};

class Graph {
public:
    int V;
    vector<vector<pair<int, int>>> adj;

    Graph(int _V) : V(_V), adj(_V) {}

    void addEdge(int u, int v, int weight) {
        adj[u].emplace_back(v, weight);
        adj[v].emplace_back(u, weight);
    }

    int primMST() {
        int minimumCost = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<bool> visited(V, false);

        pq.push({0, 0});

        while (!pq.empty()) {
            int u = pq.top().second;
            int weight = pq.top().first;
            pq.pop();


            if (visited[u]) continue;

            visited[u] = true;
            minimumCost += weight;

            for (auto neighbor : adj[u]) {
                int v = neighbor.first;
                int w = neighbor.second;
                if (!visited[v]) {
                    pq.push({w, v});
                }
            }
        }

        return minimumCost;
    }
};

int main() {
    int V, E;
    cin >> V >> E;

    Graph g(V);
    for (int i = 0; i < E; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        g.addEdge(u, v, weight);
    }

    int minimumCost = g.primMST();

    cout << "Trong so cay bao trum nho nhat: " << minimumCost << endl;

    return 0;
}
