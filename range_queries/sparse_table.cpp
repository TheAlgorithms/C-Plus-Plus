/*
Implementation of Sparse Table

Running Time Complexity
Build : O(NlogN)
Range Query : O(1)
*/


#include<vector>
#include<iostream>
#include<algorithm>


/**
 * Util function to store pre-computed logs
 */
void computeLogs(int n, std::vector<int>& logs) {
    logs[1] = 0;
    for (int i = 2 ; i < n ; i++) {
        logs[i] = logs[i/2] + 1;
    }
}

/**
 * To build Sparse Table data structure
 */
void buildTable(int n, const std::vector<int> A, const std::vector<int> logs, std::vector<std::vector<int> >& table) {
    int curLen = 0;
    for (int i = 0 ; i <= logs[n] ; i++) {
        curLen = 1 << i;
        for (int j = 0 ; j + curLen < n ; j++) {
            if (curLen == 1) {
                table[i][j] = A[j];
            }
            else {
                table[i][j] = std::min(table[i-1][j], table[i-1][j + curLen/2]);
            }
        }
    }
}

/**
 * To get the result of the query
 */
int getMinimum(int beg, int end, const std::vector<int> logs, const std::vector<std::vector<int> > table) {
    int p = logs[end - beg + 1];
    int pLen = 1 << p;
    return std::min(table[p][beg], table[p][end - pLen + 1]);
}


/**
 * Main function
 */
int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> A(n+5);
    std::vector<int> logs(n+5);
    std::vector<std::vector<int> > table(20, std::vector<int>(n+5, 0));
    for (int i = 0 ; i < n ; i++) {
        std::cin >> A[i];
    }
    computeLogs(n, logs);
    buildTable(n, A, logs, table);
    std::cout << "Minimum of the range [3, 14]: " << getMinimum(2, 13, logs, table) << std::endl;
    return 0;
}