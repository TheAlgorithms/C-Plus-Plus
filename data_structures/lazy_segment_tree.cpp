
/**
 * @file
 * @brief [Lazy Segment Tree](https://cp-algorithms.com/data_structures/segment_tree.html)
 * implementation for range updates and range queries.
 * @details A segment tree is a data structure that allows answering range
 * queries over an array effectively, while still being flexible enough to allow
 * modifying the array. Lazy propagation is an optimization to perform range
 * updates in O(log N) time.
 * @author [Yassa Talaat](https://github.com/YassaTalaat80)
 */

#include <cassert>   /// For assert
#include <iostream>  /// For IO operations
#include <vector>    /// For std::vector

/**
 * @namespace data_structures
 * @brief Data structures algorithms
 */
namespace data_structures {
/**
 * @namespace lazy_segment_tree
 * @brief Lazy Segment Tree implementation
 */
namespace lazy_segment_tree {
/**
 * @brief A struct to represent a node in the segment tree.
 * @tparam T The data type of the values stored in the tree
 */
template <typename T>
struct Node {
    T val = 0;             ///< Value stored in the node (e.g., sum of range)
    T lazy = 0;            ///< Pending update value
    bool is_lazy = false;  ///< Flag to check if there is a pending update

    Node() = default;

    Node(T x) : val(x) {}

    /**
     * @brief Apply the update to the current node and mark it as lazy for
     * children.
     * @param x The value to add
     * @param lx Left boundary of the node's range
     * @param rx Right boundary of the node's range
     */
    void add(T x, int lx, int rx) {
        val += x * (rx - lx);
        lazy += x;
        is_lazy = true;
    }
};

/**
 * @brief Class representation of the Lazy Segment Tree
 * @tparam T The data type of the values stored in the tree
 */
template <typename T>
class LazySegmentTree {
 private:
    int n = 0;                   ///< Internal size (nearest power of 2)
    std::vector<Node<T> > tree;  ///< The tree storage

    /**
     * @brief Internal merge function to combine two nodes.
     */
    Node<T> merge(const Node<T> &l, const Node<T> &r) {
        Node<T> res;
        res.val = l.val + r.val;
        return res;
    }

    /**
     * @brief Push pending updates to children nodes.
     */
    /**
     * @brief Pushes pending lazy updates to the left and right children nodes.
     * @param x The index of the current node in the tree array
     * @param lx The left boundary of the current node's segment
     * @param rx The right boundary of the current node's segment
     * @returns void
     */
    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1 || !tree[x].is_lazy)
            return;

        int mid = lx + (rx - lx) / 2;
        tree[2 * x + 1].add(tree[x].lazy, lx, mid);
        tree[2 * x + 2].add(tree[x].lazy, mid, rx);

        tree[x].lazy = 0;
        tree[x].is_lazy = false;
    }

    /**
     * @brief Recursively builds the segment tree from the given vector.
     * @param v The input vector containing initial values
     * @param x The index of the current node
     * @param lx The left boundary of the current node's segment
     * @param rx The right boundary of the current node's segment
     * @returns void
     */
    void build(const std::vector<T> &v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < v.size())
                tree[x] = Node<T>(v[lx]);
            return;
        }
        int mid = lx + (rx - lx) / 2;
        build(v, 2 * x + 1, lx, mid);
        build(v, 2 * x + 2, mid, rx);
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    /**
     * @brief Recursively applies a range update using lazy propagation.
     * @param l The left boundary of the target update range
     * @param r The right boundary of the target update range
     * @param val The value to be added to the range
     * @param x The index of the current node
     * @param lx The left boundary of the current node's segment
     * @param rx The right boundary of the current node's segment
     * @returns void
     */
    void update(int l, int r, T val, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r || rx <= l)
            return;
        if (lx >= l && rx <= r) {
            tree[x].add(val, lx, rx);
            return;
        }
        int mid = lx + (rx - lx) / 2;
        update(l, r, val, 2 * x + 1, lx, mid);
        update(l, r, val, 2 * x + 2, mid, rx);
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    /**
     * @brief Recursively queries the segment tree for the sum of a specific
     * range.
     * @param l The left boundary of the target query range
     * @param r The right boundary of the target query range
     * @param x The index of the current node
     * @param lx The left boundary of the current node's segment
     * @param rx The right boundary of the current node's segment
     * @returns The node containing the merged result of the queried range
     */
    Node<T> query(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= l && rx <= r)
            return tree[x];
        if (lx >= r || rx <= l)
            return Node<T>(0);

        int mid = lx + (rx - lx) / 2;
        Node<T> left_res = query(l, r, 2 * x + 1, lx, mid);
        Node<T> right_res = query(l, r, 2 * x + 2, mid, rx);
        return merge(left_res, right_res);
    }

 public:
    /**
     * @brief Constructs the Segment Tree and initializes the internal tree
     * array.
     * @param sz The expected number of elements in the base array
     */
    LazySegmentTree(int sz) {
        n = 1;
        while (n < sz) n *= 2;
        tree.assign(n * 2, Node<T>());
    }

    /**
     * @brief Public wrapper to build the segment tree from a vector.
     * @param v The input vector containing initial values
     * @returns void
     */
    void build(const std::vector<T> &v) { build(v, 0, 0, n); }

    /**
     * @brief Public wrapper to apply a range update.
     * @param l The left boundary of the target update range
     * @param r The right boundary of the target update range
     * @param val The value to be added to the range
     * @returns void
     */
    void update(int l, int r, T val) { update(l, r, val, 0, 0, n); }

    /**
     * @brief Public wrapper to query the segment tree for a specific range.
     * @param l The left boundary of the target query range
     * @param r The right boundary of the target query range
     * @returns The final queried value (e.g., the sum)
     */
    T query(int l, int r) { return query(l, r, 0, 0, n).val; }
};
}  // namespace lazy_segment_tree
}  // namespace data_structures

/**
 * @brief Self-test implementations
 */
static void test() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    data_structures::lazy_segment_tree::LazySegmentTree<int> st(5);
    st.build(v);

    // Initial query
    assert(st.query(0, 3) == 6);  // 1 + 2 + 3

    // Range update: add 10 to indices [0, 2] (1, 2, 3 -> 11, 12, 13)
    st.update(0, 3, 10);
    assert(st.query(0, 3) == 36);  // 11 + 12 + 13

    // Range update: add 5 to indices [2, 4] (13, 4, 5 -> 18, 9, 10)
    st.update(2, 5, 5);
    assert(st.query(2, 5) == 37);  // 18 + 9 + 10

    std::cout << "All tests passed successfully!\n";
}

/**
 * @brief Main function
 */
int main() {
    test();
    return 0;
}
