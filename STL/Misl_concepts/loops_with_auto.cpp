//auto used in range based loops
#include <bits/stdc++.h>
using namespace std;
int main()
{
    vector<pair<int, int>> v1 = {{23, 64}, {33, 78}, {12, 54}, {49, 65}};
    for (auto &x : v1) //range based auto loop with pair of int
        cout << x.first << " " << x.second << endl;

    cout << endl;

    vector<pair<int, string>> v2 = {{12, "afwafe"}, {34, "jkale"}, {23, "djaojue"}};
    for (auto &x : v2) //range based auto loop with pair of int and string
        cout << x.first << " " << x.second << endl;
}
