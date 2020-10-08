#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
template <class T>
struct fenwick {
    int siz;
    vector<T> arr;
    
    fenwick(int n) {
	siz = n;
	arr.resize(n + 1);
    }
    
    T sum(int idx) {
	T an = 0;
	while(idx > 0) {
	    an += arr[idx];
	    idx -= idx & -idx;
	}
	return an;
    }
    
    void update(int idx, T delta) {
	while (idx < siz + 1) {
	    arr[idx] += delta;
	    idx += idx & -idx;
	}
    }
    
    T query(ll l, ll r) {
	return sum(r) - sum(l - 1);
    }
};
template<class T>
struct fenwick2D{

    int siz;
    vector<fenwick<T>> arr;
    
    fenwick2D(int n) {
	siz = n;
	arr.resize(n + 1, fenwick<T>(n));
    }
    
    void update(int x, int y, T delta) {
	while(x < siz + 1) {
	    arr[x].update(y, delta);
	    x += x & -x;
	}
    }
    
    T sum(int x, int y) {
	T an = 0;
	while(x > 0) {
	    an += arr[x].sum(y);
	    x -= x & -x;
	}
	return an;
    }
    
    T query(ll x1, ll y1, ll x, ll y) {
	return sum(x, y) - sum(x1 - 1, y) - sum(x, y1 - 1) + sum(x1 - 1, y1 - 1);
    } 
    
};

int main() {
    
    
    return 0;
}
