#include <bits/stdc++.h>
using namespace std;
int main()
{
    unordered_map<string, int> m;
    int q;
    cin >> q;
    while (q--)
    {
        string stu_name;
        int Case, marks = 0;
        cin >> Case;

        if (Case == 1)
        {
            cin >> stu_name >> marks;
            m[stu_name] = m[stu_name] + marks;
        }
        else if (Case == 2)
        {
            cin >> stu_name;
            m.erase(stu_name);
        }
        else
        {
            cin >> stu_name;
            cout << m[stu_name] << endl;
        }
    }
}