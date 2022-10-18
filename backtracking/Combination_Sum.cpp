class Solution {
public:
    void findCombination(int idx, int target, vector<int> &arr, vector<vector<int>> &ans, vector<int> &ds){
    //base case
    if(idx == arr.size()){
       if(target == 0){
           ans.push_back(ds);
       }
       return;
    }
    if(arr[idx]<=target){
        ds.push_back(arr[idx]);
        findCombination(idx, target - arr[idx], arr, ans, ds);
        ds.pop_back();
    }
    findCombination(idx+1, target, arr, ans, ds);
}
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> ds;
        findCombination(0, target, candidates, ans, ds);
        return ans;
    }
};