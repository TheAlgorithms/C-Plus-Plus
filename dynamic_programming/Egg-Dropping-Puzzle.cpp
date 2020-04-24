/* Function to get minimun number of trials needed 
 * in worst case with n eggs and k floors 
 */

#include <iostream>
#include <climits>
using namespace std;

int eggDrop(int n, int k)
{
    int eggFloor[n + 1][k + 1];
    int result;

    for (int i = 1; i <= n; i++)
    {
        eggFloor[i][1] = 1; //n eggs..1 Floor
        eggFloor[i][0] = 0; //n eggs..0 Floor
    }

    // Only one egg available
    for (int j = 1; j <= k; j++)
    {
        eggFloor[1][j] = j;
    }

    for (int i = 2; i <= n; i++)
    {
        for (int j = 2; j <= k; j++)
        {
            eggFloor[i][j] = INT_MAX;
            for (int x = 1; x <= j; x++)
            {
                // 1+max(eggBreak[one less egg, lower floors],
                //       eggDoesntBreak[same # of eggs, upper floors]);
                result = 1 + max(eggFloor[i - 1][x - 1], eggFloor[i][j - x]);
                if (result < eggFloor[i][j])
                    eggFloor[i][j] = result;
            }
        }
    }

    return eggFloor[n][k];
}

int main()
{
    int n, k;
    cout << "Enter number of eggs and floors: ";
    cin >> n >> k;
    cout << "Minimum number of trials in worst case: " << eggDrop(n, k) << endl;
    return 0;
}
