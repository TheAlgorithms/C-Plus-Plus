/* Program describes usage of a popular Data Structure: Segment Trees
 *  in Finding maximum number and its index on a given Interval
 *  in logarithmic = Log(N) Time using SegmentTree Data Structures
 *  with PreProcessing O(N * Log(N)) Time
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

// Each Node contains it's value and index
struct Node {
    int val;
    int ind;
} null;

// Data Structure stores initial array and its nodes, which has the 4th size of
// the array = 4*N
struct SegmentTree {
    int N;
    std::vector<int> arr;
    std::vector<Node> nodes;
} ST;

// PreProcessing
void BuildTree_Procedural(int v, int tl, int tr) {
    if (tl == tr) {
        ST.nodes[v].val = ST.arr[tl - 1], ST.nodes[v].ind = tl;
    } else {
        int tm = (tl + tr) / 2;
        BuildTree_Procedural(2 * v, tl, tm);
        BuildTree_Procedural(2 * v + 1, tm + 1, tr);
        if (ST.nodes[2 * v].val >= ST.nodes[2 * v + 1].val)
            ST.nodes[v] = ST.nodes[2 * v];
        else
            ST.nodes[v] = ST.nodes[2 * v + 1];
    }
}

void BuildTree(std::vector<int> arr) {
    ST.N = arr.size();
    ST.arr = arr;
    ST.nodes.resize(ST.N * 4 + 1);
    BuildTree_Procedural(1, 1, ST.N);
}

// Query
Node getMaximumOnInterval_Procedural(int v, int tl, int tr, int l, int r) {
    if (l > r) return null;
    if (tl == l && tr == r) return ST.nodes[v];
    int tm = (tl + tr) / 2;
    Node p, q;
    p = getMaximumOnInterval_Procedural(2 * v, tl, tm, l, std::min(r, tm));
    q = getMaximumOnInterval_Procedural(2 * v + 1, tm + 1, tr,
                                        std::max(l, tm + 1), r);
    if (p.val > q.val)
        return p;
    else
        return q;
}

Node GetMaximumOnInterval(int l, int r) {
    return getMaximumOnInterval_Procedural(1, 1, ST.N, l, r);
}

int main() {
    // Debug
    std::vector<int> exampleArray{17, 3, 190, 2, 34, -90, 19, 100, 9};

    BuildTree(exampleArray);
    Node answer = GetMaximumOnInterval(2, 7);
    std::cout << "For array {";
    for (int i = 0; i < exampleArray.size(); i++) {
        std::cout << exampleArray[i];
        if (i != exampleArray.size() - 1) std::cout << ",";
    }
    std::cout << "} on interval (2,7) Maximum is " << answer.val << " at index "
              << answer.ind << std::endl;

    // Tests
    assert(GetMaximumOnInterval(2, 7).val == 190);
    assert(GetMaximumOnInterval(7, 10).val == 100);
    assert(GetMaximumOnInterval(6, 10).ind == 9);
    assert(GetMaximumOnInterval(6, 6).val == -90);

    return 0;
}
