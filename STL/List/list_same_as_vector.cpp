#include <bits/stdc++.h>
using namespace std;

int List()
{
    // in list everything is same as in vector the only thing is it also gives the
    // feacher for inserting an element in the front by .push_front()  operation

    list<int> a = {13, 34, 33, 332};

    a.push_back(78);
    a.push_front(6000);

    for (auto &it : a)
        cout << it << " ";

    a.pop_back();
    a.pop_front();
}
int main()
{
    List();
    return 0;
}