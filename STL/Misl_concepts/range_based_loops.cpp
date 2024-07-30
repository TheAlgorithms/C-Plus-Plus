//range based loops in stl
#include <bits/stdc++.h>
using namespace std;
int main()
{
    vector<int> v = {12, 34, 56, 87, 90};
    for (int &x : v) //range based loop =  for(int i=0;i<v.size(),i++) cout << v[i]<< endl;
        cout << x << endl;

    cout << endl;

    vector<pair<int, string>> vect = {{23, "hjhlal"}, {73, "uiouoa"}, {33, "jljlae"}};
    for (pair<int, string> &t : vect) //range based loop for pair of int and string
        cout << t.first << " " << t.second << endl;

    cout << endl;

    vector<pair<string, char>> p = {{"uieris", 'e'}, {"adfaf", 'u'}, {"ewaff", 'o'}};
    for (pair<string, char> &u : p) //range based loop for pair of  string and char
        cout << u.first << " " << u.second << endl;
}