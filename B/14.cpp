#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int countDirectedAcyclicGraphs(int V) {
    vector<vector<int>> dp(V + 1, vector<int>(V + 1, 0));

    for (int i = 1; i <= V; ++i) {
        dp[1][i] = 1;
    }

    for (int i = 2; i <= V; ++i) {
        for (int j = 1; j <= V; ++j) {
            for (int k = 1; k <= V; ++k) {
                if (k != j) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
                }
            }
        }
    }

    int result = 0;
    for (int i = 1; i <= V; ++i) {
        result = (result + dp[V][i]) % MOD;
    }

    return result;
}

int main() {
    int V;
    cin >> V;

    int result = countDirectedAcyclicGraphs(V);
    cout << "So luong do thi co huong khong co chu trinh voi " << V << " dinh la: " << result << endl;

    return 0;
}
