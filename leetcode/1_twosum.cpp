class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::vector<int> v;
        std::map<int, int> m;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (m.find(complement) != m.end()) {
                v.push_back(m.find(complement)->second);
                v.push_back(i);
                return v;
            }
            m.insert(pair<int, int>(nums[i], i));
        }

        return v;
    }
};
