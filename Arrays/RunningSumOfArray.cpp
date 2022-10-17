class Solution {
public:
    vector<int> runningSum(vector<int>& nums) 
    {
        int n=nums.size();
        vector<int> res(n);
        res[0]=nums[0];
        for(int i=1; i<n; i++)
            res[i]=nums[i]+res[i-1];
        return res;
        
    }
};
