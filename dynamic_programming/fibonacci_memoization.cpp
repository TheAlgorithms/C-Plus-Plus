#include <iostream>
#include <algorithm>
#include <cmath>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

typedef long long ll;

void solve();
ll nthFibonacci(int n, auto &map_elements);

int main() 
{
    int t = 1;
    // cin>>t;
    while(t--)
    {
       solve();
    }
    return 0;
}

void solve()
{
    int num;
    cin >> num;
    unordered_map<int,ll> map_elements;
    cout << nthFibonacci(num, map_elements);
}

ll nthFibonacci(int n, auto &map_elements)
{
    if (n <= 1)
        return n;
    if(map_elements.find(n) == map_elements.end())
    {
        map_elements.insert({n, (nthFibonacci(n-1, map_elements) + nthFibonacci(n-2,map_elements))});
    }
    return map_elements.at(n);
}