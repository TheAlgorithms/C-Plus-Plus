/**
 * @file
 * @brief Fenwick tree
 *
 * A Fenwick tree or binary indexed tree is a data structure
 * that can efficiently update elements and calculate
 * prefix sums in a table of numbers.
 */
#include <cassert>
#include <iostream>
#include <vector>

/**
 * n --> No. of elements present in input array.
 * bit[0..n] --> Array that represents Binary Indexed Tree.
 */
class FenwickTree {
    int n;
    std::vector<int> bit;

    /** Returns the highest power of two which is not more than x */
    inline int offset(int x) { return (x & (-x)); }

 public:
    /** Constructor
     * \param[in] arr --> Input array for which prefix sum is evaluated.
     */
    explicit FenwickTree(const std::vector<int>& arr) {
        n = arr.size();
        bit.assign(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            update(i, arr[i]);
        }
    }

    /** Constructor
     * \param[in] x --> Size of array that represents Binary Indexed Tree.
     */
    explicit FenwickTree(int x) {
        n = x;
        bit.assign(n + 1, 0);
    }

    /** Add val at id */
    void update(int id, int val) {
        id++;
        while (id <= n) {
            bit[id] += val;
            id += offset(id);
        }
    }

    /** Get prefix sum upto id */
    int sum(int id) {
        id++;
        int res = 0;
        while (id > 0) {
            res += bit[id];
            id -= offset(id);
        }
        return res;
    }

    /** Returns the prefix sum in range from l to r */
    int sum_range(int l, int r) { return sum(r) - sum(l - 1); }
};

/** Main function */
int main() {
    int n = 5;
    std::vector<int> arr = {1, 2, 3, 4, 5};
    FenwickTree fenwick_tree(arr);

    assert(fenwick_tree.sum_range(0, 0) == 1);
    assert(fenwick_tree.sum_range(0, 1) == 3);
    assert(fenwick_tree.sum_range(0, 2) == 6);
    fenwick_tree.update(0, 6);
    assert(fenwick_tree.sum_range(0, 0) == 6);
    assert(fenwick_tree.sum_range(0, 1) == 8);
    assert(fenwick_tree.sum_range(0, 2) == 11);
    return 0;
}
