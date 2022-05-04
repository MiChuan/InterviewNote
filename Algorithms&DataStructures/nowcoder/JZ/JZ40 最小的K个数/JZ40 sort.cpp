class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> res;
        if (input.size() == 0 || 0 == k) {
            return res;
        }
        if (input.size() <= k) {
            return input;
        }
        
        sort(input.begin(), input.end());
        res.assign(input.begin(), input.begin() + k);
        
        return res;
    }
};