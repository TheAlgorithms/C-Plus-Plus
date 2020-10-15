class Solution {
public:
    int numDecodings(string digits) {
        int n=digits.size();
        int count[n+1];
        count[0]=1;
        count[1]=1;
        if(digits[0]=='0')
            return 0;
        
        for(int i=2;i<=n;i++)
        {
            count[i]=0;
            if(digits[i-1]>'0')
            count[i]=count[i-1];
            
            if(digits[i-2]=='1'||digits[i-2]=='2'&& digits[i-1]<'7')
                count[i]+=count[i-2];
        }
    return count[n];
    }
};
