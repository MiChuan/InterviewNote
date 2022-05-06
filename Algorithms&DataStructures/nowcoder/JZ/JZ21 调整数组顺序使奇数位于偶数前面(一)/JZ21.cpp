class Solution {
public:
    vector<int> reOrderArray(vector<int>& array) {
        vector<int> res;
        int i = 0;
        for (i = 0; i < array.size(); ++i) {
            if (array[i] % 2 == 1) {
                res.push_back(array[i]);
            }
        }
        for (i = 0; i < array.size(); ++i) {
            if (array[i] % 2 == 0) {
                res.push_back(array[i]);
            }
        }
        return res;
    }
};