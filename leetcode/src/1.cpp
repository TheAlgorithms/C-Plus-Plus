/*
* Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
* You may assume that each input would have exactly one solution, and you may not use the same element twice.
*/

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> mp; // value:index
        std::vector<int> res;

        for (int i = 0; i < nums.size(); i++) {
            int diff = target - nums[i];

            if (mp.find(diff) != mp.end()) {
                res.push_back(mp[diff]);
                res.push_back(i);
                return res;
            }
            mp[nums[i]] = i;
        }
        return res;
    }
};
