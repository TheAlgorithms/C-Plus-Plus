class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
     int size= nums.size(),mul;
        vector<int>a;
        mul=1;
        for(int i=0;i<size;i++)
        {
            a.push_back(mul);
            mul*=nums[i];
        }
        mul=1;
        vector<int>b;
        for(int j=size-1;j>=0;j--)
        {
            b.push_back(mul);
            mul*=nums[j];
        }
        //return b;
        vector<int>result;
        mul=1; 
        for(int i=0,j=size-1;i<size,j>=0;j--,i++)
        {
            mul=a[i]*b[j];
            result.push_back(mul);
        }
        return result;
    }
};
