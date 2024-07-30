/*
 Multimap-> similar to maps only the difference is that we can store multiple values in a map,
 we can  store mulitple values in mulitmap
 it prints everything in sorted manner
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    multimap<string, int> m;

    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        int p;
        cin >> p;
        m.insert({s, p});
    }

    for (auto &it : m)
        cout << it.first << " " << it.second << endl;
}