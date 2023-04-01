// Implementation of the segment tree data structre
//
// Can do point updates (updates the value of some position)
// and range queries, where it gives the value of some associative
// opperation done on a range
//
// Both of these operations take O(log N) time

#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
class SegmentTree {
private:
    // Comb(ID, x) = x
    const int ID = 0;
    // Vector that represents the tree
    std::vector<int> t;
    // Size of the tree
    int size;
private:
    // Any associative function that combines x and y
    T comb(T x, T y) {
        return x + y;
    }
    int mid(int l, int r) {
        return l + (r - l) / 2;
    }
    void update(int i, int l, int r, int pos, int val) {
        if(l == r) t[i] = val;
        else {
            int m = mid(l, r);
            if(pos <= m) update(i * 2, l, m, pos, val);
            else update(i * 2 + 1, m + 1, r, pos, val);
            t[i] = comb(t[i * 2], t[i * 2 + 1]);
        }
    }
    int range_comb(int i, int l, int r, int tl, int tr) {
        if(l == tl && r == tr) return t[i];
        if(tl > tr) return 0;
        int m = mid(l, r);
        return comb(range_comb(i * 2, l, m, tl, std::min(tr, m)), range_comb(i * 2 + 1, m + 1, r, std::max(tl, m + 1), tr));
    }
public:
    // Creates a seg tree length n
    SegmentTree(int n) : t(n * 4, ID), size(n) {}
    // Updates the value at pos to val
    void update(int pos, int val) {
        update(1, 1, size, pos, val);
    }
    // Returns comb of all values between l and r
    int range_comb(int l, int r) {
        return range_comb(1, 1, size, l, r);
    }
};

// Tests the seg tree
int main() {
    SegmentTree<int> t(5);
    t.update(1, 1);
    t.update(2, 2);
    t.update(3, 3);
    t.update(4, 4);
    t.update(5, 5);
    std::cout << t.range_comb(1, 3) << "\n"; // 1 + 2 + 3 = 6
    t.update(1, 3);
    std::cout << t.range_comb(1, 3) << "\n"; // 3 + 2 + 3 = 8
}
