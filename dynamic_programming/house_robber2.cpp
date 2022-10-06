#include<bits/stdc++.h>
using namespace std;

#define lli long long int

lli solution1(vector<lli> vi)
{
    lli n = vi.size();
    lli last, sndlast;
    for (lli i = 0; i < n; i++)
    {
        if (i == 0)
        {
            last = vi[i];
            sndlast = 0;
        }
        else
        {
            lli temp1 = last;
            lli temp2 = vi[i];
            if (i > 1)
                temp2 += sndlast;
            lli curr = max(temp1, temp2);
            sndlast = last;
            last = curr;
        }
    }
    return last;
}

int main()
{
    vector<lli> arr={2,3,2};
    vector<lli> temp1,temp2;
    lli n=arr.size();
    for(lli i=0;i<n;i++)
    {
        if(i!=0)    temp1.push_back(arr[i]);
        if(i!=n-1)  temp2.push_back(arr[i]);
    }
    cout<<(solution1(temp1),solution1(temp2));
}