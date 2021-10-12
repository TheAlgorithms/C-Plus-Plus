#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int N,x,a,b,a1;
    cin>>N;
    vector<int> v;
    for(int i=0;i<N;i++)
    {
        cin>>a1;
        v.push_back(a1);
    }  
    cin>>x;
    v.erase(v.begin()+x-1);
    cin>>a>>b;
    v.erase(v.begin()+a-1,v.begin()+b-1);
    cout<<v.size()<<endl;
    for(auto it:v)
    {
        cout<<it<<" ";
    }
    return 0;
}