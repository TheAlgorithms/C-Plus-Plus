// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends


class Solution
{
    public:
    int dfs(vector<vector<int>>& M, int p, int q, const int &r, const int &s, int &f, const int &n, const int &m){
        if(p<0 || q<0 || p>=n || q>=m)
            return INT_MAX;
        if(p == r && q == s){
            f = f+M[r][s];
            return f;
        }
        M[p][q] = INT_MAX;
        int a=min(dfs(M, p-1, q, r, s, f, n, m),dfs(M, p, q-1, r, s, f, n, m));
        int b=min(dfs(M, p+1, q, r, s, f, n, m),dfs(M, p, q+1, r, s, f, n, m));
        f=f+ min(a,b);
        return f;
        // dfs(M, p+1, q, r, s, f, n, m);
        // dfs(M, p, q-1, r, s, f, n, m);
        // dfs(M, p, q+1, r, s, f, n, m);
       // M[p][q] = 3;
    }
    int minimumCostPath(vector<vector<int>>& grid) 
    {int p, q, r, s, n = grid.size(), m = grid[0].size();
      int ans = 0;
       return dfs(grid, 0, 0, n, m, ans, n, m);
       
   }
};

// { Driver Code Starts.
int main(){
	int tc;
    cout<<"Enter";
	cin >> tc;
	while(tc--){
		int n;
		cin >> n;
		vector<vector<int>>grid(n, vector<int>(n, -1));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cin >> grid[i][j];
			}
		}
		Solution obj;
		int ans = obj.minimumCostPath(grid);
		cout << ans << "\n";
	}
	return 0;
}  // } Driver Code Ends