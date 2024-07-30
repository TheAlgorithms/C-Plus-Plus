/*
given N strings, print unique strings in lexiographical order
N<=10^5
|S|<=100000
unique string ko dictionary order me print karna hai
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    set<string> s;
    int n;
    cin >> n;
    while (n--)
    {
        string str;
        cin >> str;
        s.insert(str);
    }
    for (auto &x : s)
        cout << x << endl;
}