//1->inbuild implimentation:it uses Red Black Trees
//2->Time complexcity
//3->valid keys ki datatype:-koi bhi complex datatype daal saktea hai

#include <bits/stdc++.h>
using namespace std;
int print_fun(map<int, string> &m)
{
    for (auto &m : m)
        cout << m.first << " " << m.second << endl;
}
int main()
{
    map<int, string> m;
    m[4] = "reafa", m[0] = "svfbt", m[20] = "dfafe", m[3] = "fraawe"; //pahle se hi ho ager initialization
    print_fun(m);
}
