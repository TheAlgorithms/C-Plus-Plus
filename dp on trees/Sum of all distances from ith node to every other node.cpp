//Sum of all distances from ith node to every other node
//https://leetcode.com/problems/sum-of-distances-in-tree/
vector<int> adj[30009];
class Solution
{
public:
        void dfs(int s, int p, vector<int> &subtree, int ct, vector<int> &dis)
        {
                subtree[s] = 1;
                dis[s] = ct;
                for (auto i : adj[s])
                {
                        if (i != p)
                        {
                                dfs(i, s, subtree, ct + 1, dis);
                                subtree[s] += subtree[i];
                        }
                }
        }
        int N;
        void calc(int s, int p, vector<int> &dp, vector<int> &subtree)
        {
                for (auto i : adj[s])
                {
                        if (i != p)
                        {
                                dp[i] = dp[s] + N - 2 * subtree[i];
                                calc(i, s, dp, subtree);
                        }
                }
        }
        vector<int> sumOfDistancesInTree(int n, vector<vector<int>> &edges)
        {
                vector<int> subtree(n, 0);
                vector<int> dp(n, 0);
                vector<int> dis(n, 0);
                N = n;
                for (auto i : edges)
                {
                        adj[i[0]].push_back(i[1]);
                        adj[i[1]].push_back(i[0]);
                }
                dfs(0, 0, subtree, 0, dis);
                for (int i = 0; i < n; i++)
                        dp[0] += dis[i];
                calc(0, 0, dp, subtree);
                for(int i=0;i<n;i++)
                    adj[i].clear();
                return dp;
        }
};