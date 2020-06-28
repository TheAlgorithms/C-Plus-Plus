/**
 * @file
 * @brief Implementation of [Segment
 * Trees](https://en.wikipedia.org/wiki/Segment_tree) to find maximum number in
 * an array and its index in logarithmic time - \f$O(N \log(N))\f$.
 * @author [Lasha Bukhnikashvili](author's GitHub profile link here)
 */

#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>

/**
 * We use constant variable which tells us
 * how small variables should we expect in array.
 */
const int Min_Value = -1000000000;

/**
 * Each Node contains corresponding value
 * in array and it's index
 */
struct Node {
    int val;
    int ind;
    Node() : val(Min_Value) {}
};

/**
 * Data Structure stores initial array and its nodes,
 * which has the 4th size of the array = 4*N
 */
struct SegmentTree {
    int N;
    std::vector<int> arr;
    std::vector<Node> nodes;
};

/**
 * This is a recursive method, which
 * Builds the Segment Tree in ST struct variable.
 * It should be called only once for each array.
 * Works in O(N * log N)
 *
 * Algorithm/Idea: We Start from node 1, which looks whole (1,n) interval and
 * Stores corresponding (indice and maximum values in this example) values in
 * its node. This values will be filled, once all other child-recursive methods
 * will be finished. At each Step we divide interval in 2 similar size pars, and
 * making another nodes which are corresponding segments for this parts.
 */
void BuildTree_Recusrive(SegmentTree &ST, int v, int tl, int tr) {
    if (tl == tr) {
        ST.nodes[v].val = ST.arr[tl - 1], ST.nodes[v].ind = tl;
    } else {
        int tm = (tl + tr) / 2;
        BuildTree_Recusrive(ST, 2 * v, tl, tm);
        BuildTree_Recusrive(ST, 2 * v + 1, tm + 1, tr);
        if (ST.nodes[2 * v].val >= ST.nodes[2 * v + 1].val)
            ST.nodes[v] = ST.nodes[2 * v];
        else
            ST.nodes[v] = ST.nodes[2 * v + 1];
    }
}

/**
 * This method gets initial array and builds
 * Tree Data Structure based on this array
 * and stores it in ST struct Variable
 */
void BuildTree(SegmentTree &ST, const std::vector<int> arr) {
    ST.N = arr.size();
    ST.arr = arr;
    ST.nodes.resize(ST.N * 4 + 1);
    BuildTree_Recusrive(ST, 1, 1, ST.N);
}

/**
 * This is a recursive method, which
 * Finds All Tree Nodes placed on an interval (l,r) in logarithming time
 * and gets corresponding values (Maximum in this example).
 * Works in O(log N)
 */
Node getMaximumOnInterval_Recursive(SegmentTree ST, int v, int tl, int tr,
                                    int l, int r) {
    if (l > r) return Node();
    if (tl == l && tr == r) return ST.nodes[v];
    int tm = (tl + tr) / 2;
    Node p, q;
    p = getMaximumOnInterval_Recursive(ST, 2 * v, tl, tm, l, std::min(r, tm));
    q = getMaximumOnInterval_Recursive(ST, 2 * v + 1, tm + 1, tr,
                                       std::max(l, tm + 1), r);
    if (p.val > q.val)
        return p;
    else
        return q;
}

/**
 * This method gets selected range for queury
 * and starts recursive method of getMaximumOnInterval_Recursive
 */
Node GetMaximumOnInterval(SegmentTree ST, int l, int r) {
    return getMaximumOnInterval_Recursive(ST, 1, 1, ST.N, l, r);
}

/**
 * Main function
 */
int main() {
    SegmentTree ST;
    // Debug with an example array
    std::vector<int> exampleArray{17, 3, 190, 2, 34, -90, 19, 100, 9};

    BuildTree(ST, exampleArray);

    Node answer = GetMaximumOnInterval(ST, 2, 7);
    std::cout << "For array {";
    for (int i = 0; i < (int)exampleArray.size(); i++) {
        std::cout << exampleArray[i];
        if (i != (int)exampleArray.size() - 1) std::cout << ",";
    }
    std::cout << "} on interval (2,7) Maximum is " << answer.val << " at index "
              << answer.ind << std::endl;

    // Tests
    assert(GetMaximumOnInterval(ST, 2, 7).val == 190);
    assert(GetMaximumOnInterval(ST, 7, 9).val == 100);
    assert(GetMaximumOnInterval(ST, 6, 9).ind == 8);
    assert(GetMaximumOnInterval(ST, 1, 2).ind == 1);
    assert(GetMaximumOnInterval(ST, 1, 2).val == 17);
    assert(GetMaximumOnInterval(ST, 6, 6).val == -90);
    std::cout << "All Local Tests Passed.";
    return 0;
}
