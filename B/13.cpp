#include <iostream>
#include <cmath>

using namespace std;

void generateAllDirectedGraphs(int V) {
    int numGraphs = pow(2, V * (V - 1) / 2);

    cout << "Tat ca cac do thi co huong khong chua canh song song voi " << V << " dinh:\n";

    for (int i = 0; i < numGraphs; ++i) {
        cout << "Do thi " << i + 1 << ": ";

        for (int j = 0; j < V; ++j) {
            for (int k = j + 1; k < V; ++k) {
                if (i & (1 << (k * (k - 1) / 2 + j))) {
                    cout << "(" << j << "->" << k << ") ";
                }
            }
        }

        cout << endl;
    }
}

int main() {
    int V;
    cin >> V;

    generateAllDirectedGraphs(V);

    return 0;
}
