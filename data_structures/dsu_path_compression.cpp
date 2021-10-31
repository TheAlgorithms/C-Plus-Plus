/**
 * @file
 * @brief [DSU (Disjoint
 * sets)](https://en.wikipedia.org/wiki/Disjoint-set-data_structure)
 * @details
 * It is a very powerful data structure that keeps track of different
 * clusters(sets) of elements, these sets are disjoint(doesnot have a common
 * element). Disjoint sets uses cases : for finding connected components in a
 * graph, used in Kruskal's algorithm for finding Minimum Spanning tree.
 * Operations that can be performed:
 * 1) UnionSet(i,j): add(element i and j to the set)
 * 2) findSet(i): returns the representative of the set to which i belogngs to.
 * 3) get_max(i),get_min(i) : returns the maximum and minimum
 * Below is the class-based approach which uses the heuristic of path
 * compression. Using path compression in findSet(i),we are able to get to the
 * representative of i in O(1) time.
 * @author [AayushVyasKIIT](https://github.com/AayushVyasKIIT)
 * @see dsu_union_rank.cpp
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

using std::cout;
using std::endl;
using std::vector;

/**
 * @brief Disjoint sets union data structure, class based representation.
 * @param n number of elements
 */
class dsu {
 private:
    vector<uint64_t> p;           ///< keeps track of the parent of ith element
    vector<uint64_t> depth;       ///< tracks the depth(rank) of i in the tree
    vector<uint64_t> setSize;     ///< size of each chunk(set)
    vector<uint64_t> maxElement;  ///< maximum of each set to which i belongs to
    vector<uint64_t> minElement;  ///< minimum of each set to which i belongs to
 public:
    /**
     * @brief contructor for initialising all data members.
     * @param n number of elements
     */
    explicit dsu(uint64_t n) {
        p.assign(n, 0);
        /// initially, all of them are their own parents
        for (uint64_t i = 0; i < n; i++) {
            p[i] = i;
        }
        /// initially all have depth are equals to zero
        depth.assign(n, 0);
        maxElement.assign(n, 0);
        minElement.assign(n, 0);
        for (uint64_t i = 0; i < n; i++) {
            depth[i] = 0;
            maxElement[i] = i;
            minElement[i] = i;
        }
        setSize.assign(n, 0);
        /// initially set size will be equals to one
        for (uint64_t i = 0; i < n; i++) {
            setSize[i] = 1;
        }
    }

    /**
     * @brief Method to find the representative of the set to which i belongs
     * to, T(n) = O(1)
     * @param i element of some set
     * @returns representative of the set to which i belongs to.
     */
    uint64_t findSet(uint64_t i) {
        /// using path compression
        if (p[i] == i) {
            return i;
        }
        return (p[i] = findSet(p[i]));
    }
    /**
     * @brief Method that combines two disjoint sets to which i and j belongs to
     * and make a single set having a common representative.
     * @param i element of some set
     * @param j element of some set
     * @returns void
     */
    void UnionSet(uint64_t i, uint64_t j) {
        /// check if both belongs to the same set or not
        if (isSame(i, j)) {
            return;
        }

        // we find the representative of the i and j
        uint64_t x = findSet(i);
        uint64_t y = findSet(j);

        /// always keeping the min as x
        /// shallow tree
        if (depth[x] > depth[y]) {
            std::swap(x, y);
        }
        /// making the shallower root's parent the deeper root
        p[x] = y;

        /// if same depth, then increase one's depth
        if (depth[x] == depth[y]) {
            depth[y]++;
        }
        /// total size of the resultant set
        setSize[y] += setSize[x];
        /// changing the maximum elements
        maxElement[y] = std::max(maxElement[x], maxElement[y]);
        minElement[y] = std::min(minElement[x], minElement[y]);
    }
    /**
     * @brief A utility function which check whether i and j belongs to
     * same set or not
     * @param i element of some set
     * @param j element of some set
     * @returns `true` if element `i` and `j` ARE in the same set
     * @returns `false` if element `i` and `j` are NOT in same set
     */
    bool isSame(uint64_t i, uint64_t j) {
        if (findSet(i) == findSet(j)) {
            return true;
        }
        return false;
    }
    /**
     * @brief prints the minimum, maximum and size of the set to which i belongs
     * to
     * @param i element of some set
     * @returns void
     */
    vector<uint64_t> get(uint64_t i) {
        vector<uint64_t> ans;
        ans.push_back(get_min(i));
        ans.push_back(get_max(i));
        ans.push_back(size(i));
        return ans;
    }
    /**
     * @brief A utility function that returns the size of the set to which i
     * belongs to
     * @param i element of some set
     * @returns size of the set to which i belongs to
     */
    uint64_t size(uint64_t i) { return setSize[findSet(i)]; }
    /**
     * @brief A utility function that returns the max element of the set to
     * which i belongs to
     * @param i element of some set
     * @returns maximum of the set to which i belongs to
     */
    uint64_t get_max(uint64_t i) { return maxElement[findSet(i)]; }
    /**
     * @brief A utility function that returns the min element of the set to
     * which i belongs to
     * @param i element of some set
     * @returns minimum of the set to which i belongs to
     */
    uint64_t get_min(uint64_t i) { return minElement[findSet(i)]; }
};

/**
 * @brief Self-test implementations, 1st test
 * @returns void
 */
static void test1() {
    // the minimum, maximum, and size of the set
    uint64_t n = 10;  ///< number of items
    dsu d(n + 1);     ///< object of class disjoint sets
    // set 1
    d.UnionSet(1, 2);  // performs union operation on 1 and 2
    d.UnionSet(1, 4);  // performs union operation on 1 and 4
    vector<uint64_t> ans = {1, 4, 3};
    for (uint64_t i = 0; i < ans.size(); i++) {
        assert(d.get(4).at(i) == ans[i]);  // makes sure algorithm works fine
    }
    cout << "1st test passed!" << endl;
}
/**
 * @brief Self-implementations, 2nd test
 * @returns void
 */
static void test2() {
    // the minimum, maximum, and size of the set
    uint64_t n = 10;  ///< number of items
    dsu d(n + 1);     ///< object of class disjoint sets
    // set 1
    d.UnionSet(3, 5);
    d.UnionSet(5, 6);
    d.UnionSet(5, 7);
    vector<uint64_t> ans = {3, 7, 4};
    for (uint64_t i = 0; i < ans.size(); i++) {
        assert(d.get(3).at(i) == ans[i]);  // makes sure algorithm works fine
    }
    cout << "2nd test passed!" << endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 * */
int main() {
    uint64_t n = 10;  ///< number of items
    dsu d(n + 1);     ///< object of class disjoint sets

    test1();  // run 1st test case
    test2();  // run 2nd test case

    return 0;
}
