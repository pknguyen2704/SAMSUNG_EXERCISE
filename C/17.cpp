#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
public:
    int V;
    vector<vector<int>> edges;

    Graph(int vertices) : V(vertices) {}

    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
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

    vector<vector<int>> kruskalMST() {
        vector<vector<int>> result;
        int i = 0, e = 0;
        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });

        vector<int> parent(V);
        vector<int> rank(V, 0);

        for (int node = 0; node < V; ++node) {
            parent[node] = node;
        }

        while (e < V - 1) {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];
            i++;

            int x = findParent(parent, u);
            int y = findParent(parent, v);

            if (x != y) {
                e++;
                result.push_back({u, v, w});
                unionSets(parent, rank, x, y);
            }
        }

        return result;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    vector<vector<int>> result = g.kruskalMST();

    cout << "Edges of the Minimum Spanning Tree:" << endl;
    for (const auto& edge : result) {
        cout << edge[0] << " -- " << edge[1] << " == " << edge[2] << endl;
    }

    return 0;
}
