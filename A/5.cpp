#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

    void tarjanDFS(int u, int& time, vector<int>& disc, vector<int>& low, stack<pair<int, int>>& stk) {
        disc[u] = low[u] = ++time;

        for (int v : adj[u]) {
            if (disc[v] == -1) {
                stk.push({u, v});
                tarjanDFS(v, time, disc, low, stk);

                low[u] = min(low[u], low[v]);

                if (low[v] >= disc[u]) {
                    cout << "Biconnected Component:";
                    while (!stk.empty() && stk.top() != make_pair(u, v)) {
                        cout << " (" << stk.top().first << "," << stk.top().second << ")";
                        stk.pop();
                    }
                    cout << " (" << stk.top().first << "," << stk.top().second << ")\n";
                    stk.pop();
                }
            } else if (v != disc[u] - 1 && disc[v] < low[u]) {
                low[u] = disc[v];
                stk.push({u, v});
            }
        }
    }

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool isBiconnected() {
        int time = 0;
        vector<int> disc(V, -1);
        vector<int> low(V, -1);
        stack<pair<int, int>> stk;

        tarjanDFS(0, time, disc, low, stk);
        return stk.empty();
    }
};

int main() {
    Graph g(5);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    if (g.isBiconnected()) {
        cout << "The graph is biconnected" << endl;
    } else {
        cout << "The graph is not biconnected" << endl;
    }

    return 0;
}
