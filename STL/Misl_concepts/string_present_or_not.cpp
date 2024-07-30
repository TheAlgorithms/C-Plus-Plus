/*
Given N strings and Q queries 
in each query you ae given a string print yes if string is present else no.
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    unordered_set<string> s;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        s.insert(str);
    }
    int q;
    cin >> q;
    while (q--)
    {
        string str;
        cin >> str;
        if (s.find(str) == s.end())
        {
            cout << "no" << endl;
        }
        else
        {
            cout << "yes" << endl;
        }
    }
}