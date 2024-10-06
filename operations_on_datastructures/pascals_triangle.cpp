#include <bits/stdc++.h>
using namespace std;

// Function to calculate nCr (binomial coefficient)
int nCr(int n, int r) {
    long long res = 1;
    for (int i = 0; i < r; i++) {
        res = res * (n - i);  // Multiply by (n-i) (numerator part)
        res = res / (i + 1);  // Divide by (i+1) (denominator part)x
    }
    return (int)(res);
}

vector<vector<int>> pascalTriangle(int n) {
    vector<vector<int>> ans;  // 2D vector to store the entire Pascal's Triangle
    for (int row = 1; row <= n; row++) {
        vector<int> tempLst;
        for (int col = 1; col <= row; col++) {
            tempLst.push_back(
                nCr(row - 1,
                    col - 1));  // Push the binomial coefficient C(row-1, col-1)
        }
        ans.push_back(tempLst);
    }
    return ans;
}

int main() {
    int n = 5;
    vector<vector<int>> ans = pascalTriangle(n);
    for (auto it : ans) {
        for (auto ele : it) {
            cout << ele << " ";
        }
        cout << "\n";
    }

    return 0;
}