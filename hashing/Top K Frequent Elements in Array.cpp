#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> topK(vector<int>& nums, int k) {
        unordered_map<int, int>m;
        for(int i=0; i<nums.size(); i++){
            m[nums[i]]++;
        }
        priority_queue<pair<int, int> >pq;
        for(auto itr:m){
            pq.push(make_pair(itr.second, itr.first));
        }
        vector<int> ans(k);
        for(int i=0; i<k; i++){
            auto x = pq.top();
            pq.pop();
            ans[i] = x.second;
        }
        
        return ans;
    }
};

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<int> nums(n);
        for (auto &i : nums) cin >> i;
        int k;
        cin >> k;
        Solution obj;
        vector<int> ans = obj.topK(nums, k);
        for (auto i : ans) cout << i << " ";
        cout << "\n";
    }
    return 0;
}  
