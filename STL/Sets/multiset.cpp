//multiset:-it allows multiple values to store in set(doublicates allowed in multiset)
#include <bits/stdc++.h>
using namespace std;
int print(multiset<string> &s) //&s is liye use kiya jissea iski copy na bane
{
    for (auto &x : s)
        cout << x << endl;
}
int main()
{
    multiset<string> s;
    s.insert("abc"); //O(log(n))
    s.insert("zesdf");
    s.insert("bcd");
    s.insert("abc");
    auto it = s.find("abc"); //.find() agar duplicates hai to .find() pahli copy ka itrator return karega
    if (it != s.end())
    {
        s.erase(it); //uss itrator pe jo value hai wo erase hoga
    }
    // s.erase("abc"); //iss naam ki sabhi values erase hongi
    print(s);
}