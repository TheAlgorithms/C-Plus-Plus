#include <bits/stdc++.h>
using namespace std;
int main()
{
    set<int> s;
    int t;
    cin >> t;
    while (t--)
    {
        int n, x;
        cin >> n >> x;

        if (n == 1)
        {
            s.insert(x); //s=s+x not allowed in set
        }
        else if (n == 2)
        {
            s.erase(x); //s=s-x not allowed in set
        }
        else
        {
            if (s.find(x) == s.end())
                cout << "No" << endl;
            else
                cout << "Yes" << endl;
        }
    }
}