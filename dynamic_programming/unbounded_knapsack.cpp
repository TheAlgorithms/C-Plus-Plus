include <bits/stdc++.h>
using namespace std;


// top down approach -> recursion + memoization
class Solution{
public:
    int calculateMaximumProfit(int n,int w,int val[],int wt[],int idx,vector<vector<int> >& dp){
       // base case
        if (idx == 0) {
            if (wt[0] <= w) return val[0] * (w / wt[0]);
            return 0;
           
        }
        
        if(dp[idx][w]!=-1) return dp[idx][w]; // if the dp is already calculate then no need for further go 
      
        // if a person not intereseted to pick 
        int notpick = 0 + calculateMaximumProfit(n,w,val,wt,idx-1,dp);
        int pick = INT_MIN;
      // person can pick only when if the weight of index is less or equal to the knapsack weight;
        if(wt[idx]<=w){
            pick = val[idx] + calculateMaximumProfit(n,w-wt[idx],val,wt,idx,dp);
        }
        
        return dp[idx][w] = max(pick,notpick);
        
    }
    int knapSack(int n, int w, int val[], int wt[])
    {
       
        vector<vector<int> > dp(n,vector<int> (w+1,-1));
        return calculateMaximumProfit(n,w,val,wt,n-1,dp);
    }
};
// T.C = O(n*w);
// S.C = O(n*w) + O(n); for dp (n*w) and auxiliary stack space i.e due to recursion O(n);


// bottom up approach


class Solution{
public:
   
    int knapSack(int n, int w, int val[], int wt[])
    {
        vector<vector<int> > dp(n,vector<int> (w+1,0));
        
        for(int i=0;i<=w;i++){
            dp[0][i]=(i/wt[0])*val[0];
            
        }
        for(int i=1;i<n;i++){
            for(int j=0;j<=w;j++){
                int notpick = 0 + dp[i-1][j];
                int pick = INT_MIN;
                if(wt[i]<=j){
                    pick = val[i] + dp[i][j-wt[i]];
                }
                dp[i][j]= max(pick,notpick);
            }
        }
        return dp[n-1][w];
    }
};
// T.C = O(n*w)
// S.C = O(n*w)

// more optimized space complexity

class Solution{
public:
   
    int knapSack(int n, int w, int val[], int wt[])
    {
       vector<int> prev(w+1,0),curr(w+1,0);
        for(int i=0;i<=w;i++){
            prev[i]=(i/wt[0])*val[0];
            
        }
        for(int i=1;i<n;i++){
            for(int j=0;j<=w;j++){
                int notpick = 0 + prev[j];
                int pick = INT_MIN;
                if(wt[i]<=j){
                    pick = val[i] + curr[j-wt[i]];
                }
                curr[j]= max(pick,notpick);
            }
            prev = curr;
        }
        return prev[w];
    }
};
// T.C = O(n*w)
// S.C = O(w)
// with out using 2d dp using two array only because the current state is depend on current or previous state


int main(){
  int t;
  cin>>t;
  while(t--){
    int N,W;
    cin>>N>>W;
    int val[N],wt[N};
    for(int i=0;i<N;i++) cin>>val[i];
    for(int i=0;i<N;i++) cin>>wt[i];
  
    Solution ob;
    cout<<ob.knapSack(N,W,val,wt)<<endl;
    cout<<"~"<<"\n";
    
  }
return 0;
}
