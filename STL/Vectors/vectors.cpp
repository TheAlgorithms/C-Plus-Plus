#include <bits/stdc++.h>
using namespace std;

int vector_of_vectors()
{
    int N, n;
    cin >> N >> n;

    vector<vector<int>> a;
    for (int i = 0; i < N; i++)
    {
        vector<int> temp;
        for (int j = 0; j < n; j++)
        {
            int x;
            cin >> x;
            temp.push_back(x);
        }
        a.push_back(temp);
    }
}

int main()
{
    return 0;
}
   