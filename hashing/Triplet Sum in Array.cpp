#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
    //Function to find if there exists a triplet in the 
    //array A[] which sums up to X.
    bool find3Numbers(int nums[], int n, int X)
    {
        //Your Code Here
        sort(nums, nums+n);
    
        int ans = false;  //stores the valid triplets
        
        //loop for 'a' value
        for(int i=0; i<n-2; i++){
            //now increase a untill got a different number cz wanted unique triplets
            if(i==0 || (i>0 && nums[i]!=nums[i-1])){
                //applying only when now a is different element or it is our first element
                
                //NOW 2 POINTER APPROACH
                int low = i+1;
                int high = n-1;
                int sum = X-nums[i];  //target sum
                
                //loop for 2 pointer approach
                while(low<high){
                    if(nums[low]+nums[high] == sum){
                        /*if target sum acheived by duplet tehn push that duplet along 
                        with a in ans i.e push that triplet in ans vector*/
                        
                        ans = true;
                        
                        //now inc. and dec. low and high simultaneously 
                        low++;
                        high--;
                        
                        //now inc. low until got diff element
                        while(low<high && nums[low]==nums[low-1]){
                            low++;
                        }
                        //dec high untill got diff element
                        while(low<high && nums[high]==nums[high+1]){
                            high--;
                        }
                        
                    }
                    //if target sum not foung=d then inc. or dec. low and high accordingly
                    else if(nums[low]+nums[high] < sum){
                        low++;
                    }
                    else{
                        high--;
                    }
                }
            }
        }
        return ans;
    }

};


int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,X;
		cin>>n>>X;
		int i,A[n];
		for(i=0;i<n;i++)
			cin>>A[i];
		Solution ob;
        cout <<  ob.find3Numbers(A, n, X) << endl;
    }
}
