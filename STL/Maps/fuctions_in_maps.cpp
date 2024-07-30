#include <bits/stdc++.h>
using namespace std;
int main()
{
    map<int, string> m;
    m[3] = "dfadg", m[6] = "aeig", m[8] = "jijoiej", m[0] = "ejowg";

    auto x = m.find(6); //O(lon(n))

    if (x != m.end())
        m.erase(x); //O(lon(n))--> it erases the pair which is in .find funtion.

    if (x == m.end())
        cout << "no value" << endl;

    for (auto &x : m)
        cout << x.first << " " << x.second << endl; // since this one is correct i.e (*x).first,  but this one is not i.e *x.first

    m.clear(); //it clears all the map
    for (auto &x : m)
        cout << x.first << " " << x.second << endl;
}