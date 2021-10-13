#include <cassert>   /// for assert
#include <cmath>     /// for log2
#include <iostream>  /// for io
#include <vector>    /// for vector

/**
 * @brief   Constructs the initial segment tree
 *
 * @param   arr input to construct the tree out of
 * @param   segtree the segment tree
 * @param   low inclusive lowest index of arr to begin at
 * @param   high inclusive highest index of arr to end at
 * @param   pos index of segtree to fill (eg. root node)
 * @returns void
 */
void ConsTree(const std::vector<int> &arr, std::vector<int> *segtree, int low,
              int high, int pos) {
    if (low == high) {
        (*segtree)[pos] = arr[low];
        return;
    }

    int mid = (low + high) / 2;
    ConsTree(arr, segtree, low, mid, 2 * pos + 1);
    ConsTree(arr, segtree, mid + 1, high, 2 * pos + 2);
    (*segtree)[pos] = (*segtree)[2 * pos + 1] + (*segtree)[2 * pos + 2];
}

/**
 * @brief   Returns the sum of all elements in a range
 *
 * @param   segtree the segment tree
 * @param   lazy for lazy propagation
 * @param   qlow lower index of the required query
 * @param   qhigh higher index of the required query
 * @param   low lower index of query for this function call
 * @param   high higher index of query for this function call
 * @param   pos index of segtree to consider (eg. root node)
 * @return  int result of the range query for this function call
 */
int query(std::vector<int> *segtree, std::vector<int> *lazy, int qlow,
          int qhigh, int low, int high, int pos) {
    if (low > high || qlow > high || low > qhigh) {
        return 0;
    }

    if ((*lazy)[pos] != 0) {
        (*segtree)[pos] += (*lazy)[pos] * (high - low + 1);

        if (low != high) {
            (*lazy)[2 * pos + 1] += (*lazy)[pos];
            (*lazy)[2 * pos + 2] += (*lazy)[pos];
        }
        (*lazy)[pos] = 0;
    }

    if (qlow <= low && qhigh >= high) {
        return (*segtree)[pos];
    }

    int mid = (low + high) / 2;

    return query(segtree, lazy, qlow, qhigh, low, mid, 2 * pos + 1) +
           query(segtree, lazy, qlow, qhigh, mid + 1, high, 2 * pos + 2);
}

/**
 * @brief   Updates a range of the segment tree
 *
 * @param   segtree the segment tree
 * @param   lazy for lazy propagation
 * @param   start lower index of the required query
 * @param   end higher index of the required query
 * @param   delta integer to add to each element of the range
 * @param   low lower index of query for this function call
 * @param   high higher index of query for this function call
 * @param   pos index of segtree to consider (eg. root node)
 * @returns void
 */
void update(std::vector<int> *segtree, std::vector<int> *lazy, int start,
            int end, int delta, int low, int high, int pos) {
    if (low > high) {
        return;
    }

    if ((*lazy)[pos] != 0) {
        (*segtree)[pos] += (*lazy)[pos] * (high - low + 1);

        if (low != high) {
            (*lazy)[2 * pos + 1] += (*lazy)[pos];
            (*lazy)[2 * pos + 2] += (*lazy)[pos];
        }
        (*lazy)[pos] = 0;
    }

    if (start > high || end < low) {
        return;
    }

    if (start <= low && end >= high) {
        (*segtree)[pos] += delta * (high - low + 1);

        if (low != high) {
            (*lazy)[2 * pos + 1] += delta;
            (*lazy)[2 * pos + 2] += delta;
        }

        return;
    }

    int mid = (low + high) / 2;

    update(segtree, lazy, start, end, delta, low, mid, 2 * pos + 1);
    update(segtree, lazy, start, end, delta, mid + 1, high, 2 * pos + 2);
    (*segtree)[pos] = (*segtree)[2 * pos + 1] + (*segtree)[2 * pos + 2];
}

/**
 * @brief   Self-test implementation
 *
 * @returns void
 */
static void test() {
    int max = static_cast<int>(2 * pow(2, ceil(log2(7))) - 1);
    assert(max == 15);

    std::vector<int> arr{1, 2, 3, 4, 5, 6, 7}, lazy(max), segtree(max);
    ConsTree(arr, &segtree, 0, 7 - 1, 0);

    assert(query(&segtree, &lazy, 1, 5, 0, 7 - 1, 0) == 2 + 3 + 4 + 5 + 6);

    update(&segtree, &lazy, 2, 4, 1, 0, 7 - 1, 0);
    assert(query(&segtree, &lazy, 1, 5, 0, 7 - 1, 0) == 2 + 4 + 5 + 6 + 6);

    update(&segtree, &lazy, 0, 6, -2, 0, 7 - 1, 0);
    assert(query(&segtree, &lazy, 0, 4, 0, 7 - 1, 0) == -1 + 0 + 2 + 3 + 4);
}

/**
 * @brief   Main function
 *
 * @return  0 on exit
 */
int main() {
    test();

    std::cout << "Enter number of elements: ";

    int n = 0;
    std::cin >> n;

    int max = static_cast<int>(2 * pow(2, ceil(log2(n))) - 1);
    std::vector<int> arr(n), lazy(max), segtree(max);

    int choice = 0;
    std::cout << "\nDo you wish to enter each number?:\n"
                 "1: Yes\n"
                 "0: No (default initialize them to 0)\n";

    std::cin >> choice;
    if (choice == 1) {
        std::cout << "Enter " << n << " numbers:\n";
        for (int i = 1; i <= n; i++) {
            std::cout << i << ": ";
            std::cin >> arr[i];
        }
    }

    ConsTree(arr, &segtree, 0, n - 1, 0);

    do {
        std::cout << "\nMake your choice:\n"
                     "1: Range update (input)\n"
                     "2: Range query (output)\n"
                     "0: Exit\n";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter 1-indexed lower bound, upper bound & value:\n";

            int p = 1, q = 1, v = 0;
            std::cin >> p >> q >> v;
            update(&segtree, &lazy, p - 1, q - 1, v, 0, n - 1, 0);
        } else if (choice == 2) {
            std::cout << "Enter 1-indexed lower bound & upper bound:\n";

            int p = 1, q = 1;
            std::cin >> p >> q;
            std::cout << query(&segtree, &lazy, p - 1, q - 1, 0, n - 1, 0);
            std::cout << "\n";
        }
    } while (choice > 0);

    return 0;
}
