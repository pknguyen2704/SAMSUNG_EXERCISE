#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

enum Color { UNCOLORED, RED, BLUE };

bool isBipartiteUtil(vector<vector<int>>& graph, int v, vector<Color>& colors) {
    queue<int> q;
    q.push(v);
    colors[v] = RED;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : graph[current]) {
            if (colors[current] == colors[neighbor]) {
                return false;
            }
            if (colors[neighbor] == UNCOLORED) {
                colors[neighbor] = (colors[current] == RED) ? BLUE : RED;
                q.push(neighbor);
            }
        }
    }

    return true;
}

bool isBipartite(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<Color> colors(V, UNCOLORED);

    for (int i = 0; i < V; ++i) {
        if (colors[i] == UNCOLORED) {
            if (!isBipartiteUtil(graph, i, colors)) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    vector<vector<int>> graph1 = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    cout << "Graph 1 is Bipartite: " << (isBipartite(graph1) ? "true" : "false") << endl;

    vector<vector<int>> graph2 = {{1, 2, 3}, {0, 2}, {1, 3}, {0, 2}};
    cout << "Graph 2 is Bipartite: " << (isBipartite(graph2) ? "true" : "false") << endl;

    return 0;
}
