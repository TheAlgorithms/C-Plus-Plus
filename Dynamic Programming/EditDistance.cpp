//Edit distance  - Dynamic Programming
//Given two strings,
//Find minimum number of edits (operations)
//required to convert 1st string  into 2nd string .
//Operations possible:
//a.Insert  b.Remove  c.Replace
#include<bits/stdc++.h>
using namespace std;
int mini(int x, int y, int z)
{
    return min(min(x, y), z);
}

int editDist(string str1, string str2, int m, int n)
{
    // dp table
    int dp[m+1][n+1];

    for (int i=0; i<=m; i++)
    {
        for (int j=0; j<=n; j++)
        {
            if (i==0)
                dp[i][j] = j;

            else if (j==0)
                dp[i][j] = i;

            else if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1];

            else
                dp[i][j] = 1 + mini(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]);
        }
    }

    return dp[m][n];
}

int main()
{
    string str1,str2;
    int ans;
    cout<<"Enter string 1\n";
    cin>>str1;
    cout<<"Enter string 2\n";
    cin>>str2;
    ans = editDist( str1 , str2 , str1.length(), str2.length());
    cout<<"Minimum number of moves required is : "<<ans<<endl;
    return 0;
}
