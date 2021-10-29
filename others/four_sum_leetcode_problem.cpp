/*
Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:

0 <= a, b, c, d < n
a, b, c, and d are distinct.
nums[a] + nums[b] + nums[c] + nums[d] == target
You may return the answer in any order.

Example 1:

Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
Example 2:

Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]

Constraints:

1 <= nums.length <= 200
-109 <= nums[i] <= 109
-109 <= target <= 109
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<int>> four_sum(vector<int>& nums, int target) 
{
    int n = nums.size();
    vector<vector<int>> result;
    sort(nums.begin(),nums.end());
    for(int i=0;i<n;i++)
    {
    	for(int j=i+1;j<n;j++)
        {
        	int left = j+1, right = n-1;
        	while(left < right)
            {
                int sum = nums[i] + nums[j] + nums[left] + nums[right];
            	if(sum == target)
        		{
                    result.push_back({nums[i],nums[j],nums[left],nums[right]});
            		while(left < right-2 && nums[left+1] == nums[left])
                		left++;
                	while(left < right-2 && nums[right-1] == nums[right])
                    	right--;
                	left++;
                	right--;
                }
                else if(sum < target)
            	    left++;
    		    else
                    right--;
            }
            while(j < n-1 && nums[j+1] == nums[j])
                j++;
        }
        while(i < n-1 && nums[i+1] == nums[i])
        	i++;
    }
    return result;
}
int main()
{
	int n, target;
	cin>>n; // array size
	vector<int> arr(n);
	for(int i=0;i<n;i++)
		cin>>arr[i]; // array elements
	cin>>target; // target
	vector<vector<int>> result = four_sum(arr,target); // function call
	for(int i=0;i<result.size();i++)
	{
		for(int j=0;j<result[i].size();j++)
			cout<<result[i][j]<<" "; // result 
		cout<<"\n";
	}
}