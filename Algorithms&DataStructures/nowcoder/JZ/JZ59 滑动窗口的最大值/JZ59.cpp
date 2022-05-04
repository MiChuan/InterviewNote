class Solution {
public:
    vector<int> maxInWindows(const vector<int>& nums, int size) {
        vector<int> res;
        int i, j, max;
        
        for (i = 0; i <= nums.size() - size; ++i) {
            max = nums[i];
            for (j = i; j < i + size; ++j) {
                max = max > nums[j] ? max : nums[j];
            }
            res.push_back(max);
        }
        
        return res;
    }
};