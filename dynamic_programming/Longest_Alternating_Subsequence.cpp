/*
A sequence {x1, x2, .. xn} is alternating sequence if its elements satisfy one of the following relations :
x1 < x2 > x3 < x4 > x5..... or  x1 >x2 < x3 > x4 < x5.....
Your task is to find the longest such sequence.

Example 1:

Input: nums = {1,5,4}
Output: 3
Explanation: The entire sequenece is a 
alternating sequence.


Examplae 2:

Input: nums = {1,17,5,10,13,15,10,5,16,8}
Output: 7
Explanation: There are several subsequences
that achieve this length. 
One is {1,17,10,13,10,16,8}.
*/

#include<iostream>
#include<vector>
using namespace std;

class Solution {
	public:
		int AlternatingaMaxLength(vector<int>&nums)
		{
		    int ma=1;
            int mi=1;
            int n=nums.size();

            for(int i=1;i<n;i++)
            {
                if(nums[i]>nums[i-1])
                    ma=mi+1;
                else if(nums[i]<nums[i-1])
                    mi=ma+1;
                else
                    continue;

            }

            return max(ma,mi);
    	}
};

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int n;
		cin >> n;
		vector<int>nums(n);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		Solution obj;
		int ans = obj.AlternatingaMaxLength(nums);
		cout << ans << "\n";
	}
	return 0;
}
