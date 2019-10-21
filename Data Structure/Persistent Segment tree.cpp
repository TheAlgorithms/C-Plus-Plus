#include<bits/stdc++.h>
using namespace std;

// Persistent Segment tree

const int maxn = 1e5+10;
struct node {
    int val, left, right;
};

node seg[20*maxn]; // 20 is log(n)
int root[maxn], arr[maxn], pos[maxn]; 

int tot = 0;

int clone (int x) {
    tot++;
    seg[tot] = seg[x];
    return tot;
}

int n;

int query(int a, int b, int now, int l = 1, int r = n) {
    if (a > r || b < l) return 0;
    if (a <= l && b >= r) return seg[now].val;
    int mid = (l+r)/2;
    int ans = 0;
    ans += query(a, b, seg[now].left, l, mid);
    ans += query(a, b, seg[now].right, mid+1, r);
    return ans;
}

int update(int ind, int now, int l = 1, int r = n){ 
    if (l > ind || r < ind) return now;
    if (l == r) {
        int newnode = clone(now);
        seg[newnode].val++;
        return newnode;
    }
    int mid = (l+r)/2;
    int newnode = clone(now);
    seg[newnode].left = update(ind, seg[now].left, l, mid);
    seg[newnode].right = update(ind, seg[now].right, mid+1, r);
    seg[newnode].val = seg[seg[newnode].left].val + seg[seg[newnode].right].val;
    return newnode;
}

int main(){

    return 0;
}