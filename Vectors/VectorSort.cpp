#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    vector <int>v;
    int N,a;
    cin>>N;
    for(int i=0;i<N;i++)
    {
        cin>>a;
        v.push_back(a);
    }
    sort(v.begin(),v.end());
    for(int i=0;i<N;i++)
    {
        cout<<v[i]<<" ";
    }
    return 0;
}