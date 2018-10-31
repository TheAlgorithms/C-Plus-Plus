#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> nums;

void populate()
{
    nums.resize(10);
    nums[0].push_back(0);
    nums[0].push_back(8);
    nums[1].push_back(1);
    nums[1].push_back(2);
    nums[1].push_back(4);
    nums[2].push_back(1);
    nums[2].push_back(2);
    nums[2].push_back(3);
    nums[2].push_back(5);
    nums[3].push_back(2);
    nums[3].push_back(3);
    nums[3].push_back(6);
    nums[4].push_back(1);
    nums[4].push_back(4);
    nums[4].push_back(5);
    nums[4].push_back(7);
    nums[5].push_back(2);
    nums[5].push_back(4);
    nums[5].push_back(5);
    nums[5].push_back(6);
    nums[5].push_back(8);
    nums[6].push_back(3);
    nums[6].push_back(5);
    nums[6].push_back(6);
    nums[6].push_back(9);
    nums[7].push_back(4);
    nums[7].push_back(7);
    nums[7].push_back(8);
    nums[8].push_back(0);
    nums[8].push_back(5);
    nums[8].push_back(7);
    nums[8].push_back(8);
    nums[8].push_back(9);
    nums[9].push_back(6);
    nums[9].push_back(8);
    nums[9].push_back(9);
}

int main()
{
    int t;
    cin >> t;
    populate();
    while (t--)
    {
        int n;
        cin >> n;
        int arr[10][n + 1];
        for (int i = 0; i < 10; i++)
        {
            arr[i][0] = 0;
            arr[i][1] = 1;
            arr[i][2] = nums[i].size();
        }
        for (int i = 3; i <= n; i++)
            for (int j = 0; j < 10; j++)
            {
                arr[j][i] = 0;
                for (std::size_t k = 0; k < nums[j].size(); k++)
                    arr[j][i] += arr[nums[j][k]][i - 1];
            }
        int count = 0;
        for (int i = 0; i < 10; i++)
            count += arr[i][n];
        cout << count << endl;
    }
    return 0;
}
