class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        unordered_map<int, int> mp;
        int i = 0, res;
        for (i = 0; i < numbers.size(); ++i) {
            if (mp.find(numbers[i]) == mp.end()) {
                mp[numbers[i]] = 1;
            } else {
                ++mp[numbers[i]];
            }
            if (mp[numbers[i]] >= (1 + numbers.size() / 2)) {
                res = numbers[i];
                break;
            }
        }
        return res;
    }
};