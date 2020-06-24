/**
 *
 * \file
 * \brief [Disjoint Sets Data Structure
 * (Disjoint Sets)](https://en.wikipedia.org/wiki/Disjoint-set_data_structure)
 *
 * \author [leoyang429](https://github.com/leoyang429)
 *
 * \details
 * A disjoint set data structure (also called union find or merge find set)
 * is a data structure that tracks a set of elements partitioned into a number
 * of disjoint (non-overlapping) subsets.
 * Some situations where disjoint sets can be used are-
 * to find connected components of a graph, kruskal's algorithm for finding
 * Minimum Spanning Tree etc.
 * There are two operation which we perform on disjoint sets -
 * 1) Union
 * 2) Find
 *
 */

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

vector<int> root, rank;

/**
 *
 * Function to create a set
 * @param n number of element
 *
 */
void CreateSet(int n) {
    root = vector<int>(n + 1);
    rank = vector<int>(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        root[i] = i;
    }
}

/**
 *
 * Find operation takes a number x and returns the set to which this number
 * belongs to.
 * @param x element of some set
 * @return set to which x belongs to
 *
 */
int Find(int x) {
    if (root[x] == x) {
        return x;
    }
    return root[x] = Find(root[x]);
}

/**
 *
 * A utility function to check if x and y are from same set or not
 * @param x element of some set
 * @param y element of some set
 *
 */
bool InSameUnion(int x, int y) { return Find(x) == Find(y); }

/**
 *
 * Union operation combines two disjoint sets to make a single set
 * in this union function we pass two elements and check if they are
 * from different sets then combine those sets
 * @param x element of some set
 * @param y element of some set
 *
 */
void Union(int x, int y) {
    int a = Find(x), b = Find(y);
    if (a != b) {
        if (rank[a] < rank[b]) {
            root[a] = b;
        } else if (rank[a] > rank[b]) {
            root[b] = a;
        } else {
            root[a] = b;
            ++rank[b];
        }
    }
}

/** Main function */
int main() {
    // tests CreateSet & Find
    int n = 100;
    CreateSet(n);
    for (int i = 1; i <= 100; ++i) {
        if (root[i] != i) {
            cout << "Fail" << endl;
            break;
        }
    }
    // tests InSameUnion & Union
    cout << "1 and 2 are initially not in the same subset" << endl;
    if (InSameUnion(1, 2)) {
        cout << "Fail" << endl;
    }
    Union(1, 2);
    cout << "1 and 2 are now in the same subset" << endl;
    if (!InSameUnion(1, 2)) {
        cout << "Fail" << endl;
    }
    return 0;
}
