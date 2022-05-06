class Solution {
public:
    vector<int> printNumbers(int n) {
        vector<int> res;
        int max = pow(10, n) - 1, i = 0;
        for (int i = 0; i < max; ++i) {
            res.push_back(i + 1);
        }
        return res;
    }
};