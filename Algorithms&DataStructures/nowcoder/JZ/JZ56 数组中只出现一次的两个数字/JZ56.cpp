class Solution {
public:
    vector<int> FindNumsAppearOnce(vector<int>& array) {
        vector<int> res;
        //用于将所有的数异或起来
        int k = 0;
        for(int num: array) {
            k ^= num;
        }
        //获得k中最低位的1
        int mask = 1;
        while((k & mask) == 0) {
            mask <<= 1;
        }
        int a = 0;
        int b = 0;
        for(int num: array) {
            if((num & mask) == 0) {
                a ^= num;
            } else {
                b ^= num;
            }
        }
        res.push_back(a), res.push_back(b);
        sort(res.begin(), res.end());
        return res;
    }
};