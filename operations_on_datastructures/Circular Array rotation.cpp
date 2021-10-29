#include <bits/stdc++.h>
using namespace std;

int main()
{

    long n, k, q, i;
    long arr[100000];
    cin >> n >> k >> q;
    long r = k % n;
    for (i = r; i < n; i++)
        cin >> arr[i];
    for (i = 0; i < r; i++)
        cin >> arr[i];
    for (i = 0; i < q; i++)
    {
        cin >> k;
        cout << arr[k];
    }
    return 0;
}