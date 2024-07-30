#include <bits/stdc++.h>
using namespace std;

int explainVectors()
{
    vector<int> a = {19, 23, 43, 53, 535, 23123, 2, 321, 24};

    // erase a single element in vector
    a.erase(a.begin() + 1); // it deletes the 23 from vector

    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "------------------------" << endl;

    vector<int> a1 = {11, 22, 433, 33, 363, 123, 32, 3421, 524};
    // erase elements from a index to another index
    //[a,b)
    a1.erase(a1.begin() + 1, a1.begin() + 3); // it delets the elements from 22 to 33( 33 is excluded )
    for (int i = 0; i < a1.size(); i++)
    {
        cout << a1[i] << " ";
    }
}

int main()
{
    explainVectors();
    return 0;
}