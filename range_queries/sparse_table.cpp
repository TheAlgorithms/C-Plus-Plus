/**
 * @file sparse_table.cpp
 * @brief Implementation of [Sparse Table](https://en.wikipedia.org/wiki/Range_minimum_query) data structure
 *
 * @details
 * Sparse Table is a data structure, that allows answering range queries.
 * It can answer most range queries in O(logn), but its true power is answering range minimum queries
 * or equivalent range maximum queries). For those queries it can compute the answer in O(1) time.
 *
 * * Running Time Complexity \n
 * * Build : O(NlogN) \n
 * * Range Query : O(1) \n
*/

#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

/**
 * @namespace range_queries
 * @brief Range Queries algorithms
 */
namespace range_queries {
/**
 * @namespace sparse_table
 * @brief Range queries using sparse-tables
 */
 namespace sparse_table {
/**
 * This function precomputes intial log table for further use.
 * @param n value of the size of the input array
 * @return corresponding vector of the log table
 */
template<typename T>
std::vector<T> computeLogs(const std::vector<T>& A) {
    int n = A.size();
    std::vector<T> logs(n);
    logs[1] = 0;
    for (int i = 2 ; i < n ; i++) {
        logs[i] = logs[i/2] + 1;
    }
    return logs;
}

/**
 * This functions builds the primary data structure sparse table
 * @param n value of the size of the input array
 * @param A array of the input integers
 * @param logs array of the log table
 * @return created sparse table data structure
 */
template<typename T>
std::vector<std::vector<T> > buildTable(const std::vector<T>& A, const std::vector<T>& logs) {
    int n = A.size();
    std::vector<std::vector<T> > table(20, std::vector<T>(n+5, 0));
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
template<typename T>
int getMinimum(int beg, int end, const std::vector<T>& logs, const std::vector<std::vector<T> >& table) {
    int p = logs[end - beg + 1];
    int pLen = 1 << p;
    return std::min(table[p][beg], table[p][end - pLen + 1]);
}
}
} // namespace range_queries

/**
 * Main function
 */
int main() {
    std::vector<int> A{1, 2, 0, 3, 9};
    std::vector<int> logs = range_queries::sparse_table::computeLogs(A);
    std::vector<std::vector<int> >  table = range_queries::sparse_table::buildTable(A, logs);
    assert(range_queries::sparse_table::getMinimum(0, 0, logs, table) == 1);
    assert(range_queries::sparse_table::getMinimum(0, 4, logs, table) == 0);
    assert(range_queries::sparse_table::getMinimum(2, 4, logs, table) == 0);
    return 0;
}

