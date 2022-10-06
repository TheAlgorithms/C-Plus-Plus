#include <iostream>
#include <vector>
using namespace std;

int calls = 0;

void print(vector<int> &v)
{
    for (auto i : v)
        cout << i << " ";
    cout << "\n";
}

void diceSumHelper(int dice, int desiredSum, vector<int> &v)
{
    ++calls;
    // if (desiredSum < 0)
    //     return;
    if (dice == 0)
    {
        if (desiredSum == 0)
            print(v);
    }
    else if (desiredSum >= dice && desiredSum <= dice * 6)
    // further optimise code, from 9k calls to 200 calls
    // pruning the call tree
    {
        for (int i = 1; i <= 6; ++i)
        {
            // choose
            v.push_back(i);

            // explore
            diceSumHelper(dice - 1, desiredSum - i, v);

            // un-choose
            v.pop_back();
        }
    }
}

void diceSum(int dice, int desiredSum)
{
    vector<int> v;
    diceSumHelper(dice, desiredSum, v);
}

int main()
{
    diceSum(5, 7);
    cout << calls << "\n";
    return 0;
}