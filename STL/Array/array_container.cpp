//array container in c++ stl
#include <iostream>
#include <array> //herder of array container
using namespace std;
int main()
{
    array<int, 5> arr = {10}; //array container reprentation.
                              //only zeroth index has the element 10 and rest of other elements of remaing indicies are automaticly assinged to zero i.e {10,0,0,0,0}

    for (auto i : arr)
        cout << i << " "; //  for (int i = 0; i < 5; i++) cout << arr[i] <<" ";

    cout << endl;

    arr.fill(10);      //  ".fill()"  it makes all the elements 10 from  zeroth to (n-1)th index. i.e {10,10,10,10,10}
    for (auto i : arr) //  for(int i=0;i<5;i++) cout<<it[i];
        cout << i << " ";

    cout << endl;

    string str = "llablnlf";
    for (auto i : str)
        cout << i;

    cout << endl
         << endl;
}