#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    long long sum = 0, sum1 = 0;
    cin >> t;
    while (t--)
    {
        int len, max_ele;
        cin >> len >> max_ele;
        map<int, int> v;
        for (auto &x : v)
        {
            v.insert({})
                v[x]++;
        }
        for (int i = 0; i < len; i++)
        {
            if (max_ele == 1)
                sum = max(v[0], v[i]);
            else if (max_ele > 1)
                for (auto &x : v)
                    sum1 = x.first + sum1;
        }
        if (max_ele == 1)
            cout << sum << endl;
        else
            cout << sum1 + sum << endl;
    }
}