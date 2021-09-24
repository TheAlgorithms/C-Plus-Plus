// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends

class Solution
{
    public:
    //Function to return max value that can be put in knapsack of capacity W.
    int knapSack(int W, int wt[], int val[], int N) 
    { 
       // Your code here
       int dp[2][W+1];
       for(int i=0;i<2;i++){
           for(int  j=0;j<=W;j++)
           dp[i][j]=0;
       }
       
       
       
      int count=0;
      
       for(int i=0;i<N;i++){
           int row=(count%2)?1:0;
           int alternate=!(row);
        for(int j=1;j<=W;j++){
            if(wt[count]>j)
            {
                dp[row][j]=dp[alternate][j];
                
            }
            else
            dp[row][j]=max(dp[alternate][j-wt[i]]+val[i],dp[alternate][j]);
            
        }   
           count++;
           
       }
       
       int finalrow=!(N%2);
       
      return dp[finalrow][W];
       
       
    }
};

// { Driver Code Starts.

int main()
 {
    //taking total testcases
    int t;
    cin>>t;
    while(t--)
    {
        //reading number of elements and weight
        int n, w;
        cin>>n>>w;
        
        int val[n];
        int wt[n];
        
        //inserting the values
        for(int i=0;i<n;i++)
            cin>>val[i];
        
        //inserting the weights
        for(int i=0;i<n;i++)
            cin>>wt[i];
        Solution ob;
        //calling method knapSack()
        cout<<ob.knapSack(w, wt, val, n)<<endl;
        
    }
	return 0;
}  // } Driver Code Ends
