#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    vector<ll> arr = {4, 5, 6, 8, 99, 101};

    ll key = 8;
    auto a = lower_bound(arr.begin(), arr.end(), key);
    auto b = upper_bound(arr.begin(), arr.end(), key);

    cout << (b - a) << endl;
    cout << *b << " " << *a << endl;
    cout << &b << " " << &a << endl;

    vector<ll> arr1 = {5, 6, 7, 8, 9, 8975, 10000000};
    auto x = equal_range(arr.begin(), arr.end(), key);

    cout << (x.second - x.first) << endl;
    cout << *x.second << " " << *x.first << endl;

    return 0;
}