#include<bits/stdc++.h>
using namespace std;
    int findDuplicate(vector<int>& nums) {
        int slow=nums[0];
        int fast=nums[0];
        do{
            slow=nums[slow];
            fast=nums[nums[fast]];
        }while(slow!=fast);
        slow=nums[0];
        while(slow!=fast)
        {
            slow=nums[slow];
            fast=nums[fast];
        }
        return slow;
    }
int main()
{
    vector <int> A;
    int t,temp,ans;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        cin>>temp;
        A.push_back(temp);
    }
    ans=findDuplicate(A);
    cout<<ans;
    return 0;
}