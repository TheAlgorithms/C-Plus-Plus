#include <bits/stdc++.h>
using namespace std;

int explainVectors()
{
    vector<int> a = {19, 23, 43, 53, 535, 23123, 2, 321, 24};
    vector<int> a2 = {93, 434, 42, 32, 32, 3245, 453};

    a.swap(a2); // it swaps the vector a and a2( all the elements of a transffered to a2 and all the elements of a2 transferred to a)

    for (auto &it : a)
        cout << it << " ";

    cout << endl
         << "------------------" << endl;

    for (auto &it : a2)
        cout << it << " ";

    a.pop_back(); // it deletes the last  element of the vector a

    a.clear(); // it trims down a vector into an empty vector

    cout << (a.empty()) << endl; // .empty return true if the vector is an empty vector
}
int main()
{
    explainVectors();
    return 0;
}