//itrators with vectors
#include <bits/stdc++.h>
using namespace std;
int main()
{
    vector<int> v = {32, 12, 54, 90, 45, 34};
    vector<int>::iterator it;
    for (it = v.begin(); it != v.end(); ++it)
    {
        cout << (*(it)) << endl;
    }
}