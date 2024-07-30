//collection of values i. keys:-sets
#include <bits/stdc++.h>
using namespace std;
int print(set<string> &s)
{
    for (auto &value : s)
    {
        cout << value << endl;
    }
}
int main()
{
    set<string> s;
    s.insert("acv"); //O(lon(n))
    s.insert("iej");
    s.insert("fweq");
    s.insert("rwd");
    auto it = s.find("acv");
    if (it != s.end())
    {
        // cout << (*it) << endl;
        s.erase(it);
    }
    //   s.erase("acv");
    print(s);
}