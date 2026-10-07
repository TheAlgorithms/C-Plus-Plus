/**
 * @file
 * @brief [Fenwick Tree](https://en.wikipedia.org/wiki/Fenwick_tree) algorithm
 * implementation
 * @details
 * _From Wikipedia, the free encyclopedia._
 *
 * A Fenwick tree or binary indexed tree (BIT) is a clever implementation of a
 * datastructure called bionomal tree. It can update values and solve range
 * queries with operations that is; commulative, associative and has an
 * inverse for this type of element. It can also solve immutable range queries
 * (min/max), when operations only are associative over this type of element.
 * Some of these restrictions can be removed, by storing redunant information;
 * like in max/min range queries.
 *
 * @author [Mateusz Grzegorzek](https://github.com/mateusz-grzegorzek)
 * @author [David Leal](https://github.com/Panquesito7)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace
 * @brief Range Queries
 */
namespace range_queries {
/**
 * @brief The class that initializes the Fenwick Tree.
 */
class fenwick_tree {
    size_t n = 0;            ///< No. of elements present in input array
    std::vector<int> bit{};  ///< Array that represents Binary Indexed Tree.

    /**
     * @brief Returns the highest power of two which is not more than `x`.
     * @param x Index of element in original array.
     * @return Offset of index.
     */
    inline int offset(int x) { return (x & (-x)); }
 public:
    /**
     * @brief Class Constructor
     * @tparam T the type of the array
     * @param[in] arr Input array for which prefix sum is evaluated.
     * @return void
     */
    template <typename T>
    explicit fenwick_tree(const std::vector<T>& arr) : n(arr.size()) {
        bit.assign(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            update(i, arr[i]);
        }
    }

    /**
     * @brief Class Constructor
     * @tparam T the type of the variable
     * @param[in] x Size of array that represents Binary Indexed Tree.
     * @return void
     */
    template <typename T>
    explicit fenwick_tree(T x) : n(x) { bit.assign(n + 1, 0); }

    /**
     * @brief Updates the value of an element in original array and
     * accordingly updates the values in BIT array.
     * @tparam T the type of the variables
     * @param id Index of element in original array.
     * @param val Value with which element's value is updated.
     * @return void
     */
    template <typename T>
    void update(T id, T val) {
        id++;
        while (id <= n) {
            bit[id] += val;
            id += offset(id);
        }
    }

    /**
     * @brief Returns the sum of elements in range from 0 to ID.
     * @tparam T the type of the variables
     * @param id Index in original array up to which sum is evaluated.
     * @return Sum of elements in range from 0 to id.
     */
    template <typename T>
    int sum(T id) {
        id++;
        T res = 0;
        while (id > 0) {
            res += bit[id];
            id -= offset(id);
        }
        return res;
    }

    /**
     * @brief Returns the prefix sum in range from L to R.
     * @param l Left index of range.
     * @param r Right index of range.
     * @return Sum of elements in range from L to R.
     */
    int sum_range(int l, int r) { return sum(r) - sum(l - 1); }
};
}  // namespace range_queries

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    range_queries::fenwick_tree fenwick_tree(arr);

    assert(fenwick_tree.sum_range(0, 0) == 1);
    assert(fenwick_tree.sum_range(0, 1) == 3);
    assert(fenwick_tree.sum_range(0, 2) == 6);
    assert(fenwick_tree.sum_range(0, 3) == 10);
    assert(fenwick_tree.sum_range(0, 4) == 15);

    fenwick_tree.update(0, 6);
    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}
