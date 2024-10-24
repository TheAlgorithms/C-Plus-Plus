#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int unbounded_knapsack(int n, vector<int> wt, vector<int> val, int w) {
    vector<vector<int>> dp(n + 1, vector<int>(w + 1, 0));
    for (int j = 0; j <= w; ++j) {
        if (wt[0] <= j) {
            dp[0][j] = (j / wt[0]) * val[0];
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= w; ++j) {
            int nottake = dp[i - 1][j];
            int take = 0;
            if (j >= wt[i]) {
                take = val[i] + dp[i][j - wt[i]];
            }
            dp[i][j] = max(take, nottake);
        }
    }

    return dp[n - 1][w];
}
int main() {
    int n = 5;
    vector<int> wt = {1, 2, 3, 4, 5};
    vector<int> val = {6, 1, 2, 3, 7};
    int w = 7;
    cout << "Maximum value of items is" << unbounded_knapsack(n, wt, val, w);
    return 0;
}