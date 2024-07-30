/*
we have the array a={24 22 37 35 92 24 22 35 97 37}
find the frequency of each distict element in the array in a sorted manner
and also the size of new array
*/
/*
NOTE-> since the question states that in a sorted order, if a question ask for only frequency, without the
sorted or unsorted, then we can use  unordered_map to save log(n) time complexity.
*/

#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    map<int, int> a; // unordered_map if there is no sorted manner is required
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        a[x]++;
    }
    for (auto &it : a)
        cout << it.first << " " << it.second << endl;

    cout << endl;
    cout << "size= " << a.size() << endl;
}