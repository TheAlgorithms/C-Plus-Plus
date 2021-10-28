class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> Lis(n,1);
        vector<int> siz(n,1);
        int maxx = 1;
        for(int i = 1;i<n;i++)
        {
            for(int j = 0;j<i;j++)
            {
                if(nums[i]>nums[j])
                {
                    if(Lis[i] < 1+Lis[j])
                    {
                        Lis[i] = 1 + Lis[j];
                        siz[i] = siz[j];
                    }
                    else if(Lis[i] == 1+Lis[j])
                    {
                        siz[i] += siz[j];
                    }
                }
                maxx = max(maxx,Lis[i]);
            }
        }
        
        int count = 0;
        for(int i = 0;i<n;i++)
        {
            if(Lis[i] == maxx)
            {count += siz[i];}
        }
        return count;
        
    }
};
