#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Edge {
    int u, v, weight;
    Edge(int _u, int _v, int _weight) : u(_u), v(_v), weight(_weight) {}
};

class Graph {
public:
    int V;
    vector<Edge> edges;

    Graph(int _V) : V(_V) {}

    void addEdge(int u, int v, int weight) {
        edges.emplace_back(u, v, weight);
    }

    int find(int parent[], int node) {
        if (parent[node] == -1)
            return node;
        return find(parent, parent[node]);
    }

    void Union(int parent[], int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);
        parent[rootX] = rootY;
    }

    bool isCyclic(int parent[], int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);
        return rootX == rootY;
    }

    int reverseDeleteMST() {
        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return a.weight > b.weight;
        });

        int *parent = new int[V];
        fill(parent, parent + V, -1);

        for (Edge edge : edges) {
            int u = edge.u;
            int v = edge.v;


            if (!isCyclic(parent, u, v)) {
                cout << "Xoa canh (" << u << ", " << v << ") co trong so " << edge.weight << endl;
                Union(parent, u, v);
            }
        }

        int minWeight = accumulate(edges.begin(), edges.end(), 0, [](int sum, const Edge &e) {
            return sum + e.weight;
        });

        delete[] parent;
        return minWeight;
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

    int minWeight = g.reverseDeleteMST();

    cout << "Trong so cay bao trum nho nhat sau khi xoa: " << minWeight << endl;

    return 0;
}
