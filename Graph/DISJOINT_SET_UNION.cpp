//CODEFORCES 217 A
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include <stdio.h>
#include <stack>
#include <algorithm>
#include <list>
#include <utility>
#include <ctime>
#include <memory.h>
#include <assert.h>
#include <stdlib.h>
#include <cmath>
#include <limits.h>
#include <sstream>
#include <bitset>

#define FOR(i,start,end) for(size_t i=start;i<end;i++)
#define rFOR(i,end,start) for(size_t i=end,i>=start;i--)
#define ll long long int
#define ld long double
#define si(x) scanf("%d",&x)
#define sl(x) scanf("%lld",&x)
#define sd(x) scanf("%lf",&x)
#define sc(x) scanf("%c",&x)
#define ss(x) scanf("%s",x)
#define vl vector<ll>
#define vi vector<int>
#define vvl vector< vl >
#define vvi vector< vi >
#define pb push_back
#define mp make_pair
#define max_int_value 2147483647
#define max_long_value 9223372036854775807
#define ii pair<ll,ll>
#define F first
#define S second
#define fast_io ios_base::sync_with_stdio(0);cin.tie(0)

using namespace std;

void printArray(int arr[] , int n){ FOR(i,0,n) cout << arr[i] << " " ; cout << endl;}

vector< int > parent;

void init(int n){
	parent.resize(n);
	FOR(i,0,n) parent[i] = i;
}

int find(int k){
	if(parent[k]==k) return k;
	else return parent[k] = find(parent[k]);
}

void unite(int a, int b){
	parent[find(b)] = find(a);
}

int main() {
    fast_io;
    int n;
    cin >> n;
    vector< ii > a(n);
    init(n);
    FOR(i,0,n) {
   		cin >> a[i].F >> a[i].S;
   	}
   	FOR(i,0,n){
   		FOR(j,i+1,n){
   			if(a[i].F==a[j].F || a[i].S==a[j].S){
   				unite(i,j);
   			}
   		}
   	}
    set<int> b;
    for(int i=0;i<n;i++){
    	b.insert(find(i));
    }
    cout << b.size()-1 << endl;
    return 0;
}
