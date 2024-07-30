#include <bits/stdc++.h>
using namespace std;

int main()
{
    int key1 = 87, key2 = 7;
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    bool firt = binary_search(arr.begin(), arr.end(), key1);
    bool secd = binary_search(arr.begin(), arr.end(), key2);

    cout << firt << " " << secd << endl;

    return 0;
}