#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
public:
    int V; // Số đỉnh
    vector<vector<pair<int, int>>> adjList; // Danh sách kề (có trọng số)

    Graph(int vertices) : V(vertices), adjList(vertices) {}

    void addEdge(int u, int v, int w) {
        adjList[u].emplace_back(v, w);
        adjList[v].emplace_back(u, w);
    }

    void dfs(int u, vector<int>& disc, vector<int>& low, vector<int>& parent, vector<int>& weight, int& time, vector<pair<int, int>>& bridges) {
        disc[u] = low[u] = ++time;

        for (const auto& edge : adjList[u]) {
            int v = edge.first;
            int w = edge.second;

            if (disc[v] == -1) {
                parent[v] = u;
                weight[v] = w;

                dfs(v, disc, low, parent, weight, time, bridges);

                low[u] = min(low[u], low[v]);

                if (low[v] > disc[u]) {
                    // Cạnh (u, v) là cầu
                    bridges.emplace_back(u, v);
                }
            } else if (v != parent[u]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    vector<pair<int, int>> findBridges() {
        vector<int> disc(V, -1);
        vector<int> low(V, -1);
        vector<int> parent(V, -1);
        vector<int> weight(V, -1);
        vector<pair<int, int>> bridges;
        int time = 0;

        for (int i = 0; i < V; ++i) {
            if (disc[i] == -1) {
                dfs(i, disc, low, parent, weight, time, bridges);
            }
        }

        return bridges;
    }

    vector<pair<int, int>> findCriticalEdges() {
        vector<pair<int, int>> bridges = findBridges();

        // Tạo đồ thị cầu
        Graph bridgeGraph(bridges.size());
        for (size_t i = 0; i < bridges.size(); ++i) {
            int u = bridges[i].first;
            int v = bridges[i].second;
            int w = weight[v];
            bridgeGraph.addEdge(u, v, w);
        }

        // Tìm cây bao trùm nhỏ nhất trên đồ thị cầu (cây bao trùm của các SCC)
        vector<pair<int, int>> mstEdges = bridgeGraph.kruskalMST();

        return mstEdges;
    }

    vector<pair<int, int>> kruskalMST() {
        vector<pair<int, int>> result;
        sort(adjList.begin(), adjList.end(), [](const vector<pair<int, int>>& a, const vector<pair<int, int>>& b) {
            return a[0].second < b[0].second;
        });

        vector<int> parent(V);
        vector<int> rank(V, 0);

        for (int node = 0; node < V; ++node) {
            parent[node] = node;
        }

        for (const auto& edgesFromNode : adjList) {
            for (const auto& edge : edgesFromNode) {
                int u = edgesFromNode[0].first;
                int v = edge.first;
                int w = edge.second;

                int x = findParent(parent, u);
                int y = findParent(parent, v);

                if (x != y) {
                    result.emplace_back(u, v);
                    unionSets(parent, rank, x, y);
                }
            }
        }

        return result;
    }

    int findParent(vector<int>& parent, int i) {
        if (parent[i] == i)
            return i;
        return findParent(parent, parent[i]);
    }

    void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
        int xRoot = findParent(parent, x);
        int yRoot = findParent(parent, y);

        if (rank[xRoot] < rank[yRoot])
            parent[xRoot] = yRoot;
        else if (rank[xRoot] > rank[yRoot])
            parent[yRoot] = xRoot;
        else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 0, 1);
    g.addEdge(1, 3, 4);
    g.addEdge(3, 4, 5);
    g.addEdge(4, 3, 6);

    vector<pair<int, int>> criticalEdges = g.findCriticalEdges();

    cout << "Critical Edges:" << endl;
    for (const auto& edge : criticalEdges) {
        cout << edge.first << " -- " << edge.second << endl;
    }

    return 0;
}
