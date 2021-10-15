#include <bits/stdc++.h>
#define mod 1000000007
#define ll long long
using namespace std;

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<int> arr;

    //insert in a vector
    arr.push_back(1);
    arr.push_back(2);

    //access vector elements
    cout<<arr[0]<<" "<<arr[1]<<endl;

    //check size of vector
    cout<<arr.size()<<endl;

    //sort a vector
    sort(arr.begin(),arr.end());

    //iterating over vector, way #1:
    for(int i=0;i<arr.size();i++)
        cout<<arr[i]<<" ";
    cout<<endl;

    //iterating over vector, way #2:
    for(auto it=arr.begin();it!=arr.end();it++)
        cout<<*it<<" ";
    cout<<endl;
}
