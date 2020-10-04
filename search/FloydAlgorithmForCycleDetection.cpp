
/*Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

There is only one duplicate number in nums, return this duplicate number in O(1) space and time complexity less than O(n^2) without modifying the original array.

Example-:
    Input: 5
           3 1 3 4 2
    
    Output: 3
*/
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
