#include <bits/stdc++.h>
using namespace std;


class Solution{
    
    void Solve(int i, int j, vector<vector<int>> &m, string out, vector<string> &ans, int n, vector<vector<int>> &visited){
        if(i==n-1 && j == n-1){
            ans.push_back(out);
            return;
        }
        
        if(i+1<n && !visited[i+1][j] && m[i+1][j]==1){
            visited[i][j]=1;
            out.push_back('D');
            Solve(i+1, j, m, out, ans, n, visited);
            out.pop_back();
            visited[i][j]=0;
        }
        if(j-1>=0 && !visited[i][j-1] && m[i][j-1]==1){
            visited[i][j]=1;
            out.push_back('L');
            Solve(i, j-1, m, out, ans, n, visited);
            out.pop_back();
            visited[i][j]=0;
        }
        if(j+1<n && !visited[i][j+1] && m[i][j+1]==1){
            visited[i][j]=1;
            out.push_back('R');
            Solve(i, j+1, m, out, ans, n, visited);
            out.pop_back();
            visited[i][j]=0;
        }
        if(i-1>=0 && !visited[i-1][j] && m[i-1][j]==1){
            visited[i][j]=1;
            out.push_back('U');
            Solve(i-1, j, m, out, ans, n, visited);
            out.pop_back();
            visited[i][j]=0;
        }
    }
    
    public:
    vector<string> findPath(vector<vector<int>> &m, int n) {
        // Your code goes here
        string out = "";
        vector<string> ans;
        
        vector<vector<int >> v(n, vector<int>(n, 0));
        
        if(m[0][0]==1){
            Solve(0, 0, m, out, ans, n, v);
        }
        return ans;
    }
};


int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> m(n, vector<int> (n,0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> m[i][j];
            }
        }
        Solution obj;
        vector<string> result = obj.findPath(m, n);
        if (result.size() == 0)
            cout << -1;
        else
            for (int i = 0; i < result.size(); i++) cout << result[i] << " ";
        cout << endl;
    }
    return 0;
}  // } Driver Code Ends
