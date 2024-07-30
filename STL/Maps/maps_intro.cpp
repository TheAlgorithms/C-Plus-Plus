#include <bits/stdc++.h>
using namespace std;
int main()
{
    map<int, string> m;
    m[1] = "asd";
    m[1] = "fvr";
    m[4] = "reafa", m[0] = "svfbt", m[20] = "dfafe", m[3] = "fraawe"; //pahle se hi ho ager initialization

    for (auto &x : m)
        cout << x.first << " " << x.second << endl;

    cout << endl
         << "user input" << endl;

    map<int, string> m1;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) //maps user input
    {
        int y;
        string p;
        cin >> y >> p;
        m1[y] = p;
    }
    cout << endl;
    for (auto &e : m1)
        cout
            << e.first << " " << e.second << endl;
}
