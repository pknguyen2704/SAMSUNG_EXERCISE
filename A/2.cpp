#include <iostream>
#include <cmath>

using namespace std;

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int combination(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int countGraphs(int V, int E) {
    if (V < 0 || E < 0 || E > combination(V - 1, 2)) {
        return 0; 
    }

    return combination(V - 1, 2) / combination(E, 1);
}

int main() {
    int V, E;
    cin >> V;
    cin >> E;

    int result = countGraphs(V, E);
    cout << "So luong do thi vo huong khac nhau la: " << result << endl;

    return 0;
}
