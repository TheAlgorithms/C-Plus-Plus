/**
 * @file
 * @brief Given a 2D array print it in reverse spiral form
 */
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>

using namespace std;
vector<int> reverseSpiral(int R, int C, vector<vector<int>> &a)
{
    vector<int> spiral;
    int l = 0, k = 0, last_row = R - 1, last_col = C - 1;
    while (l <= last_row && k <= last_col)
    {
        // for storing top row
        for (int i = l; i <= last_col; i++)
        {
            spiral.push_back(a[k][i]);
        }
        k += 1;

        // for storing rigtmost col
        for (int i = k; i <= last_row; i++)
        {
            spiral.push_back(a[i][last_col]);
        }
        last_col -= 1;

        // for storing bottom row
        if (k <= last_row)
        {
            for (int i = last_col; i >= l; i--)
            {
                spiral.push_back(a[last_row][i]);
            }
            last_row -= 1;
        }

        // for storing leftmost col
        if (l <= last_col)
        {
            for (int i = last_row; i >= k; i--)
            {
                spiral.push_back(a[i][l]);
            }
            l += 1;
        }
        // repeat this process until whole matrix is not traverse!!
    }
    
    // we need to reverse it because we traverse in normal spiral form.
    reverse(begin(spiral), end(spiral));
    return spiral;
}


int main()
{
    int R, C;
    cin >> R >> C;
    vector<vector<int>> a; 
  
    for(int i = 0; i < R; i++)
    {
        vector<int>temp;
        for(int j = 0; j < C; j++)
        {
            int t;
            cin>>t;
            temp.push_back(t);
        }
        a.push_back(temp);
    }
    vector<int> ans = reverseSpiral(R, C, a);
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}