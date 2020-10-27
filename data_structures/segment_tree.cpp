#include <vector>

using namespace std;

struct SegmentTree {
    int size;
    vector<long long> arr;
    vector<long long> tree;

    SegmentTree(vector<long long> array) {
        size = array.size();

        arr = array;
        tree.resize(size * 4);

        init(1, 0, size - 1);
    }

    long long operation(long long x, long long y) { return x + y; }

    long long init(int node, int start, int end) {
        if (start == end)
            return tree[node] = arr[start];
        int mid = (start + end) / 2;

        return tree[node] = operation(init(node * 2, start, mid),
                                      init(node * 2 + 1, mid + 1, end));
    }

    void update(int node, int start, int end, int index, long long diff) {
        if (index < start || index > end)
            return;
        tree[node] = tree[node] + diff;

        if (start != end) {
            update(node * 2, start, (start + end) / 2, index, diff);
            update(node * 2 + 1, (start + end) / 2 + 1, end, index, diff);
        }
    }

    void update(int index, long long diff) {
        update(1, 0, size - 1, index, diff);
    }

    void update_range(int node, int start, int end, int left, int right,
                      long long diff) {
        if (left > end || right < start)
            return;
        if (start == end) {
            tree[node] += diff;
            return;
        }

        int mid = (start + end) / 2;
        update_range(node * 2, start, mid, left, right, diff);
        update_range(node * 2 + 1, mid + 1, end, left, right, diff);
        tree[node] = operation(tree[node * 2], tree[node * 2 + 1]);
    }

    void update_range(int left, int right, long long diff) {
        update_range(1, 0, size - 1, left, right, diff);
    }

    long long query(int node, int start, int end, int left, int right) {
        if (right < start || end < left)
            return 0;
        if (left <= start && end <= right)
            return tree[node];

        int mid = (start + end) / 2;
        return operation(query(node * 2, start, mid, left, right),
                         query(node * 2 + 1, mid + 1, end, left, right));
    }

    long long query(int left, int right) {
        return query(1, 0, size - 1, left, right);
    }
};