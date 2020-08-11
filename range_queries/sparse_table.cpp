/**
 * @file sparse_table.cpp
 * @brief Implementation of [Sparse Table](https://en.wikipedia.org/wiki/Range_minimum_query) data structure
 *
 * @details
 * Sparse Table is a data structure, that allows answering range queries.
 * It can answer most range queries in O(logn), but its true power is answering range minimum queries
 * or equivalent range maximum queries). For those queries it can compute the answer in O(1) time.
 *
 * Running Time Complexity \n
 * Build : O(NlogN) \n
 * Range Query : O(1) \n
*/

#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

/**
 * @namespace range_queries
 * @brief Range Queries algorithms
 */
namespace SparseTable {
/**
 * This function precomputes intial log table for further use.
 * @param n value of the size of the input array
 * @return corresponding vector of the log table
 */
std::vector<int> computeLogs(int n) {
    std::vector<int> logs(n+5);
    logs[1] = 0;
    for (int i = 2 ; i < n ; i++) {
        logs[i] = logs[i/2] + 1;
    }
    return logs;
}

/**
 * This functions builds the primary data structure Sparse Table
 * @param n value of the size of the input array
 * @param A array of the input integers
 * @param logs array of the log table
 * @return created sparse table data structure
 */
std::vector<std::vector<int> > buildTable(int n, const std::vector<int>& A, const std::vector<int>& logs) {
    std::vector<std::vector<int> > table(20, std::vector<int>(n+5, 0));
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
    return table;
}

/**
 * This function is the query function to get the range minimum value
 * @param beg beginning index of the query range
 * @param end ending index of the query range
 * @param logs array of the log table
 * @param table sparse table data structure for the input array
 * @return minimum value for the [beg, end] range for the input array
 */
int getMinimum(int beg, int end, const std::vector<int>& logs, const std::vector<std::vector<int> >& table) {
    int p = logs[end - beg + 1];
    int pLen = 1 << p;
    return std::min(table[p][beg], table[p][end - pLen + 1]);
}
} // namespace range_queries

/**
 * Main function
 */
int main() {
    int n = 5;
    std::vector<int> A = {1, 2, 0, 3, 9};
    std::vector<int> logs = SparseTable::computeLogs(n);
    std::vector<std::vector<int> >  table = SparseTable::buildTable(n, A, logs);
    assert(SparseTable::getMinimum(0, 0, logs, table) == 1);
    assert(SparseTable::getMinimum(0, 4, logs, table) == 0);
    assert(SparseTable::getMinimum(2, 4, logs, table) == 0);
    std::cout<<"Tests passed" << std::endl;
    return 0;
}
