#include <bits/stdc++.h>
using namespace std;

void solution(int idx, int arr[], int n, vector<int> ans)
{
    if (idx >= n)
    {
        if (sizeof(ans) == 0)
            cout << "_";
        else
        {
            for (int i = 0; i < sizeof(ans); i++)
            {
                cout << ans[i] << "_";
            }
        }
        cout << endl;
        return;
    }
    solution(idx + 1, arr, n, ans);
    ans.push_back(arr[idx]);
    solution(idx + 1, arr, n, ans);
}

int main()
{
    int arr[] = {3, 1, 2};
    vector<int> ans;
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << n << endl;
    solution(0, arr, n, ans);
}