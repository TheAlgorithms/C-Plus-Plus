#include <iostream>
#include <vector>
using namespace std;

void permuteHelper(vector<int> &nums, vector<vector<int>> &ans, vector<int> &chosen)
{
    if (nums.size() == 0)
    {
        ans.push_back(chosen); // successful permutation
        return;
    }
    else
    {
        for (int i = 0; i < nums.size(); ++i)
        {
            // CHOOSE
            chosen.push_back(nums[i]);    // {1}
            nums.erase(nums.begin() + i); // {2, 3, 4}

            // EXPLORE REMAINING OPTIONS
            permuteHelper(nums, ans, chosen);

            // UNCHOOSE
            nums.insert(nums.begin() + i, chosen.back());
            chosen.pop_back();
        }
    }
}

void permute(vector<int> nums)
{
    vector<vector<int>> ans;
    vector<int> current;
    permuteHelper(nums, ans, current);

    for (auto v : ans)
    {
        for (auto i : v)
            cout << i << " ";
        cout << "\n";
    }
}

int main()
{
    vector<int> nums = {1, 2, 3};
    permute(nums);
    return 0;
}