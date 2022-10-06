// memoiazed solution

#include<bits/stdc++.h>
using namespace std;


int solution(int idx, vector<int> vi, vector<int> &dp)
{
    if (idx == 0) // it means we have picked 2 index
        return vi[idx];
    if (idx < 0) // it means we have picked 1 index
        return 0;
    if (dp[idx] != -1)
        return dp[idx];
    int pick = vi[idx] + solution(idx - 2, vi, dp);
    int notpick = 0 + solution(idx - 1, vi, dp);

    return dp[idx] = max(pick, notpick);
}

// tabulation solution

int solution1(vector<int> vi)
{
    int n=vi.size(); 
    //vector<int> dp(n);
    int last,sndlast;
    for(int i=0;i<n;i++)
    {
        if(i==0)
        {
            last=vi[i];
            sndlast=0;
        }
        else
        {
            int temp1=last;
            int temp2=vi[i];
            if(i>1)
                temp2+=sndlast;
            int curr=max(temp1,temp2);
            sndlast=last;
            last = curr;
        }
    }
    return last;
}
 
int main()
{
    vector<int> vi={2,1,4,9};
    vector<int> dp(5,-1);
    int n=sizeof(vi)/sizeof(vi[0]);
    //cout<<solution(n,vi,dp);
    cout<<solution1(vi);
}