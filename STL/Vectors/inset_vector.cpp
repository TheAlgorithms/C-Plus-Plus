#include <bits/stdc++.h>
using namespace std;

int explainVectors()
{
    vector<int> a = {19, 23, 43, 53, 535, 23123, 2, 321, 24};

    // insert a elment right ater the first elment of the vector
    a.insert(a.begin() + 1, 223); // 223 will be insereted right after 19

    for (auto &it : a)
        cout << it << " ";

    cout << endl
         << "---------------------------------" << endl;

    vector<int> a1 = {82, 34, 25, 67, 43, 25, 90};
    // insert a element at the first poisition of the vector
    a1.insert(a1.begin(), 98); // 98 will be inserted at the begining of the vector

    for (auto &it : a1)
        cout << it << " ";

    cout << endl
         << "---------------------------------" << endl;

    vector<int> a2 = {86, 343, 89467, 6237, 2343, 5325, 9230};
    // insert n occurrences of of element x inside the vector
    int n = 2, x = 100;
    a2.insert(a2.begin() + 1, n, x); // this will inset two occurences of 100 after the first elmeent of the veector

    for (auto &it : a2)
        cout << it << " ";

    cout << endl
         << "---------------------------------" << endl;

    vector<int> a3 = {93, 434, 42, 32, 32, 3245, 453};
    // inset a vector into another vector
    a3.insert(a3.begin() + 1, a2.begin(), a2.end()); // it insets the entire vector a2 into the vector a3,
    // after the first element of the vector a3 ( we can change the position of insetion according to requirement).

    for (auto &it : a3)
        cout << it << " ";
}

int main()
{
    explainVectors();
    return 0;
}