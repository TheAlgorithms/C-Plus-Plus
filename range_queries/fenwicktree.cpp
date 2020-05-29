#include<iostream>
using namespace std;

/**
 * ` lowbit(x) ` aims to find the last 1 in binary of a positive number
 * twos complement works good on this
 * also using ` x - (x & (x - 1)) `
 */
#define lowbit(x) (x & (-x) )

const int maxn = 1e5 + 7;
int tree[maxn] = {0},
                 range;             // segement of [1...range], notice it must be less than `maxn`

void update(int x, int c) {
    while(x <= range) {
        tree[x] += c;
        x += lowbit(x);
    }
}
int query(int x) {
    int ans = 0;
    while(x) {
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
}
int query_segement(int l, int r) {
    return query(r) - query(l - 1);
}

int main() {
    cin >> range;
    for(int i = 1; i <= range; i++) {
        int num;
        cin >> num;
        update(i, num);
    }
    int q;
    cin >> q;
    while(q--) {
        int op;
        cin >> op;
        if(op == 0) {
            int l, r;
            cin >> l >> r;
            cout << query_segement(l, r) << endl;
        } else {
            int x, c;
            cin >> x >> c;
            update(x, c);
        }
    }
    return 0;
}
