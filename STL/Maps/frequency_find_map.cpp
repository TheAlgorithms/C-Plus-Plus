// 1:-Ordered map
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
/*
2:-Unordered map.
Given N string and Q queries.
In each query you are given a string
print frequency of that string

N<=1e6
|S|<=100
Q<=1e6

Input:
5
asd
sdf
asd
sdf
ghj
3
asd
ghj
sdf

Expected Output
2
1
2
// */
// #include <bits/stdc++.h>
// using namespace std;
// int main()
// {
//     unordered_map<string, int> m;
//     int n;
//     cin >> n;
//     for (int i = 0; i < n; i++)
//     {
//         string s;
//         cin >> s;
//         m[s]++;
//     }
//     int q;
//     cin >> q;
//     while (q--)
//     {
//         string s;
//         cin >> s;
//         cout << m[s] << endl;
//     }
// }