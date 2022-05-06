class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        unordered_map<char, int> count;
        int i = 0;
        for (i = 0; i < str .size(); ++i) {
            if (count.find(str[i]) != count.end()) {
                ++count[str[i]];
            } else {
                count[str[i]] = 1;
            }
        }
        for (i = 0; i < str .size(); ++i) {
            if (count[str[i]] == 1) {
                return i;
            }
        }
        return -1;
    }
};