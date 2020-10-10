//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
constexpr unsigned int max_height = 400000;
void ConsTree(std::vector<int> arr, std::vector<int> segtree, long long low,
              long long high, long long pos) {
    if (low == high) {
        segtree[pos] = arr[low];
        return;
    }
    long long mid = (low + high) / 2;
    ConsTree(arr, segtree, low, mid, 2 * pos + 1);
    ConsTree(arr, segtree, mid + 1, high, 2 * pos + 2);
    segtree[pos] = segtree[2 * pos + 1] + segtree[2 * pos + 2];
}
long long query(std::vector<int> segtree, std::vector<int> lazy, long long qlow,
                long long qhigh, long long low, long long high, long long pos) {
    if (low > high) {
        return 0;
    }
    if (qlow > high || qhigh < low) {
        return 0;
    }
    if (lazy[pos] != 0) {
        segtree[pos] += lazy[pos] * (high - low + 1);
        if (low != high) {
            lazy[2 * pos + 1] += lazy[pos];
            lazy[2 * pos + 2] += lazy[pos];
        }
        lazy[pos] = 0;
    }
    if (qlow <= low && qhigh >= high) {
        return segtree[pos];
    }
    long long mid = (low + high) / 2;
    return query(segtree, lazy, qlow, qhigh, low, mid, 2 * pos + 1) +
           query(segtree, lazy, qlow, qhigh, mid + 1, high, 2 * pos + 2);
}
void update(std::vector<int> segtree, std::vector<int> lazy, long long start,
            long long end, long long delta, long long low, long long high,
            long long pos) {
    if (low > high) {
        return;
    }
    if (lazy[pos] != 0) {
        segtree[pos] += lazy[pos] * (high - low + 1);
        if (low != high) {
            lazy[2 * pos + 1] += lazy[pos];
            lazy[2 * pos + 2] += lazy[pos];
        }
        lazy[pos] = 0;
    }
    if (start > high || end < low) {
        return;
    }
    if (start <= low && end >= high) {
        segtree[pos] += delta * (high - low + 1);
        if (low != high) {
            lazy[2 * pos + 1] += delta;
            lazy[2 * pos + 2] += delta;
        }
        return;
    }
    long long mid = (low + high) / 2;
    update(segtree, lazy, start, end, delta, low, mid, 2 * pos + 1);
    update(segtree, lazy, start, end, delta, mid + 1, high, 2 * pos + 2);
    segtree[pos] = segtree[2 * pos + 1] + segtree[2 * pos + 2];
}
int main() {
    ;
    long long n = 0, c = 0;
    std::cin >> n >> c;
    long long p = 0, q = 0, v = 0, choice = 0;
    std::vector<int> arr(n);
    std::vector<int> segtree(max_height);
    std::vector<int> lazy = {0};
    ConsTree(arr, segtree, 0, n - 1, 0);
    while (c--) {
        std::cin >> choice;
        if (choice == 0) {
            std::cin >> p >> q >> v;
            update(segtree, lazy, p - 1, q - 1, v, 0, n - 1, 0);
        } else {
            std::cin >> p >> q;
            std::cout << query(segtree, lazy, p - 1, q - 1, 0, n - 1, 0)
                      << "\n";
        }
    }
    return 0;
}
