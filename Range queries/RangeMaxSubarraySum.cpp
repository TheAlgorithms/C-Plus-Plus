#include<bits/stdc++.h>
using namespace std;

struct A {
    long long sum, l, r, mx;
    A operator + (const A & o) const {
        A temp;
        temp.sum = sum + o.sum;
        temp.l = max(max(l, sum), sum + o.l);
        temp.r = max(max(o.r, o.sum), o.sum + r);
        temp.mx = max(max(max(max(mx, o.mx), r + o.l), temp.l), temp.r);
        return temp;
    }
};

int n, m;
int a[200200];
A seg[800800];

void build(int l = 1, int r = n, int now = 1){
    if(l == r){
        seg[now] = {a[l], a[l], a[l], a[l]};
        return;
    }
    int mid = (l+r)/2;
    build(l, mid, now*2);
    build(mid+1, r, now*2+1);
    seg[now] = seg[now*2] + seg[now*2+1];
    // cerr << now << ' ' << seg[now].sum << ' ' << seg[now].l << ' ' << seg[now].r << ' ' << seg[now].mx << endl;
}

A query(int a, int b, int l = 1, int r = n, int now = 1) {
    if (r < a or l > b) return {0, 0, 0};
    if (l >= a and r <= b) {
        // cerr << now << ' ' << seg[now].best << ' ' << seg[now].mx << ' '  << seg[now].mn << endl;
        return seg[now];
    }
    int mid = (l+r)/2;
    A q1 = query(a, b, l, mid, now*2);
    A q2 = query(a, b, mid+1, r, now*2+1);
    // cerr << "combined " << max(max(q1.best, q2.best), q2.mx - q1.mn) << ' ' <<  max(q1.mx, q2.mx) << ' ' << min(q1.mn, q2.mn) << endl;
    return q1+q2;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    build();
    for(int i = 1; i <= m; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%lld\n", query(x+1, y+1).mx);
    }
    return 0;
}