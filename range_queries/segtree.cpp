#include <cmath>    /// for log2
#include <iostream> /// for io

void ConsTree(long long arr[], long long segtree[],
              int low, int high, int pos) {
    if (low == high) {
        segtree[pos] = arr[low];
        return;
    }

    int mid = (low + high) / 2;
    ConsTree(arr, segtree, low, mid, 2 * pos + 1);
    ConsTree(arr, segtree, mid + 1, high, 2 * pos + 2);
    segtree[pos] = segtree[2 * pos + 1] + segtree[2 * pos + 2];
}

long long query(long long segtree[], long long lazy[],
                int qlow, int qhigh, int low, int high, int pos) {
    if (low > high || qlow > high || low > qhigh)
        return 0;

    if (lazy[pos] != 0) {
        segtree[pos] += lazy[pos] * (high - low + 1);

        if (low != high) {
            lazy[2 * pos + 1] += lazy[pos];
            lazy[2 * pos + 2] += lazy[pos];
        }
        lazy[pos] = 0;
    }

    if (qlow <= low && qhigh >= high)
        return segtree[pos];

    int mid = (low + high) / 2;

    return query(segtree, lazy, qlow, qhigh, low, mid, 2 * pos + 1) +
           query(segtree, lazy, qlow, qhigh, mid + 1, high, 2 * pos + 2);
}

void update(long long segtree[], long long lazy[],
            int start, int end, int delta, int low, int high, int pos) {
    if (low > high)
        return;

    if (lazy[pos] != 0) {
        segtree[pos] += lazy[pos] * (high - low + 1);

        if (low != high) {
            lazy[2 * pos + 1] += lazy[pos];
            lazy[2 * pos + 2] += lazy[pos];
        }
        lazy[pos] = 0;
    }

    if (start > high || end < low)
        return;

    if (start <= low && end >= high) {
        segtree[pos] += delta * (high - low + 1);

        if (low != high) {
            lazy[2 * pos + 1] += delta;
            lazy[2 * pos + 2] += delta;
        }

        return;
    }

    int mid = (low + high) / 2;

    update(segtree, lazy, start, end, delta, low, mid, 2 * pos + 1);
    update(segtree, lazy, start, end, delta, mid + 1, high, 2 * pos + 2);
    segtree[pos] = segtree[2 * pos + 1] + segtree[2 * pos + 2];
}

int main() {
    std::cout << "Enter number of elements: ";

    int n;
    std::cin >> n;

    int max = 2 * pow(2, ceil(log2(n))) - 1;
    long long arr[n] = {0}, lazy[max] = {0}, segtree[max];

    ConsTree(arr, segtree, 0, n - 1, 0);

    int choice;
    do {
        std::cout << "\nMake your choice:\n"
                     "1: Range update (input)\n"
                     "2: Range query (output)\n"
                     "0: Exit\n";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter 1-indexed lower bound, upper bound & value:\n";

            int p, q, v;
            std::cin >> p >> q >> v;
            update(segtree, lazy, p - 1, q - 1, v, 0, n - 1, 0);
        } else if (choice == 2) {
            std::cout << "Enter 1-indexed lower bound & upper bound:\n";

            int p, q;
            std::cin >> p >> q;
            std::cout << query(segtree, lazy, p - 1, q - 1, 0, n - 1, 0);
            std::cout << "\n";
        }
    } while (choice > 0);

    return 0;
}
