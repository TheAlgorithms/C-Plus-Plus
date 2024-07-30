/*
Given N strings, print unique strings
in lexiographical order with their
frequency
and maximum frequency

N<=10^5
|S| <= 100
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int mx = INT_MIN;
    int n;
    cin >> n;
    map<string, int> m;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        m[s]++;

        mx = max(m[s], mx);
    }
    for (auto &it : m)
        cout << it.first << " " << it.second << endl;

    cout << mx << endl;

    return 0;
}