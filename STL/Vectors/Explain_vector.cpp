#include <bits/stdc++.h>
using namespace std;

int explainVectors()
{
    vector<int> a = {19, 23, 43, 53, 53, 23123, 2, 321, 24};

    // printing the first element in vector
    cout << a.front();

    // printing the last element in vecoter
    cout << a.back();

    //    printing vectors using iterators
    vector<int>::iterator it;

    //  for printing in sequence
    for (it = a.begin(); it != a.end(); it++)
        cout << (*it) << endl;

    cout << "----------------------------------------" << endl;
    // for printing in reverse order
    for (it = a.end() - 1; it != a.begin(); it--)
        cout << (*it) << endl;

    // short cut for iterator
    for (auto &it : a)
        cout << it << endl;
}

int main()
{
    explainVectors();
    return 0;
}