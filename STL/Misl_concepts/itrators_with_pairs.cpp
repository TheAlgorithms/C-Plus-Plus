//itrators with pairs
#include <bits/stdc++.h>
using namespace std;
int main()
{
    vector<pair<int, int>> r = {{23, 54}, {84, 90}, {38, 78}};
    vector<pair<int, int>>::iterator it; //declartion of itrators
    for (it = r.begin(); it != r.end(); ++it)
        cout << (*it).first << " " << (*it).second << endl;

    cout << "\n"
         << endl;

    for (it = r.begin(); it != r.end(); ++it)
        cout << it->first << " " << it->second << endl;

    //since,it->first == (*it).first  and  it->second == (*it).second
}