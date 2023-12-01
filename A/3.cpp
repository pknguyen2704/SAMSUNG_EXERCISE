// Phát hiện cạnh song song
// Thiết kế một thuật toán tuyến tính để đếm số cạnh song song trong một đồ thị

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph {
    int V; 
    list<int> *edges;

    public:
        Graph(int V);
        void addEdge(int v, int w);
        int countParallelEdges();
};

Graph::Graph(int V) {
    this->V = V;
    edges = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    edges[v].push_back(w);
    edges[w].push_back(v);
}

int Graph::countParallelEdges() {
    int parallelEdges = 0;

    for (int i = 0; i < V; ++i) {
        vector<bool> visited(V, false);

        for (auto j = edges[i].begin(); j != edges[i].end(); ++j) {
            if (!visited[*j]) {
                visited[*j] = true;
                parallelEdges += distance(edges[*j].begin(), edges[*j].end()) - 1;
            }
        }
    }
    return parallelEdges / 2;
}

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);
    g.addEdge(0, 2);

    cout << "Số cạnh song song: " << g.countParallelEdges() << endl;

    return 0;
}
