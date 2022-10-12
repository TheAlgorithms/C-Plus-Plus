/**
 * @file
 * @brief [DSU (Disjoint
 * sets)](https://en.wikipedia.org/wiki/Disjoint-set-data_structure)
 * @details
 * dsu : It is a very powerful data structure which keeps track of different
 * clusters(sets) of elements, these sets are disjoint(doesnot have a common
 * element). Disjoint sets uses cases : for finding connected components in a
 * graph, used in Kruskal's algorithm for finding Minimum Spanning tree.
 * Operations that can be performed:
 * 1) UnionSet(i,j): add(element i and j to the set)
 * 2) findSet(i): returns the representative of the set to which i belogngs to.
 * 3) getParents(i): prints the parent of i and so on and so forth.
 * Below is the class-based approach which uses the heuristic of union-ranks.
 * Using union-rank in findSet(i),we are able to get to the representative of i
 * in slightly delayed O(logN) time but it allows us to keep tracks of the
 * parent of i.
 * @author [AayushVyasKIIT](https://github.com/AayushVyasKIIT)
 * @see dsu_path_compression.cpp
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
    vector<uint64_t> p;        ///< keeps track of the parent of ith element
    vector<uint64_t> depth;    ///< tracks the depth(rank) of i in the tree
    vector<uint64_t> setSize;  ///< size of each chunk(set)
 public:
    /**
     * @brief constructor for initialising all data members
     * @param n number of elements
     */
    explicit dsu(uint64_t n) {
        p.assign(n, 0);
        /// initially all of them are their own parents
        depth.assign(n, 0);
        setSize.assign(n, 0);
        for (uint64_t i = 0; i < n; i++) {
            p[i] = i;
            depth[i] = 0;
            setSize[i] = 1;
        }
    }
    /**
     * @brief Method to find the representative of the set to which i belongs
     * to, T(n) = O(logN)
     * @param i element of some set
     * @returns representative of the set to which i belongs to
     */
    uint64_t findSet(uint64_t i) {
        /// using union-rank
        while (i != p[i]) {
            i = p[i];
        }
        return i;
    }
    /**
     * @brief Method that combines two disjoint sets to which i and j belongs to
     * and make a single set having a common representative.
     * @param i element of some set
     * @param j element of some set
     * @returns void
     */
    void unionSet(uint64_t i, uint64_t j) {
        /// checks if both belongs to same set or not
        if (isSame(i, j)) {
            return;
        }
        /// we find representative of the i and j
        uint64_t x = findSet(i);
        uint64_t y = findSet(j);

        /// always keeping the min as x
        /// in order to create a shallow tree
        if (depth[x] > depth[y]) {
            std::swap(x, y);
        }
        /// making the shallower tree, root parent of the deeper root
        p[x] = y;

        /// if same depth, then increase one's depth
        if (depth[x] == depth[y]) {
            depth[y]++;
        }
        /// total size of the resultant set
        setSize[y] += setSize[x];
    }
    /**
     * @brief A utility function which check whether i and j belongs to same set
     * or not
     * @param i element of some set
     * @param j element of some set
     * @returns `true` if element i and j are in same set
     * @returns `false` if element i and j are not in same set
     */
    bool isSame(uint64_t i, uint64_t j) {
        if (findSet(i) == findSet(j)) {
            return true;
        }
        return false;
    }
    /**
     * @brief Method to print all the parents of i, or the path from i to
     * representative.
     * @param i element of some set
     * @returns void
     */
    vector<uint64_t> getParents(uint64_t i) {
        vector<uint64_t> ans;
        while (p[i] != i) {
            ans.push_back(i);
            i = p[i];
        }
        ans.push_back(i);
        return ans;
    }
};
/**
 * @brief Self-implementations, 1st test
 * @returns void
 */
static void test1() {
    /* checks the parents in the resultant structures */
    uint64_t n = 10;   ///< number of elements
    dsu d(n + 1);      ///< object of class disjoint sets
    d.unionSet(2, 1);  ///< performs union operation on 1 and 2
    d.unionSet(1, 4);
    d.unionSet(8, 1);
    d.unionSet(3, 5);
    d.unionSet(5, 6);
    d.unionSet(5, 7);
    d.unionSet(9, 10);
    d.unionSet(2, 10);
    // keeping track of the changes using parent pointers
    vector<uint64_t> ans = {7, 5};
    for (uint64_t i = 0; i < ans.size(); i++) {
        assert(d.getParents(7).at(i) ==
               ans[i]);  // makes sure algorithm works fine
    }
    cout << "1st test passed!" << endl;
}
/**
 * @brief Self-implementations, 2nd test
 * @returns void
 */
static void test2() {
    // checks the parents in the resultant structures
    uint64_t n = 10;   ///< number of elements
    dsu d(n + 1);      ///< object of class disjoint sets
    d.unionSet(2, 1);  /// performs union operation on 1 and 2
    d.unionSet(1, 4);
    d.unionSet(8, 1);
    d.unionSet(3, 5);
    d.unionSet(5, 6);
    d.unionSet(5, 7);
    d.unionSet(9, 10);
    d.unionSet(2, 10);

    /// keeping track of the changes using parent pointers
    vector<uint64_t> ans = {2, 1, 10};
    for (uint64_t i = 0; i < ans.size(); i++) {
        assert(d.getParents(2).at(i) ==
               ans[i]);  /// makes sure algorithm works fine
    }
    cout << "2nd test passed!" << endl;
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test1();  // run 1st test case
    test2();  // run 2nd test case

    return 0;
}
