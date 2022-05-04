class Solution {
public:
    vector<string> res;
    
    vector<string> Permutation(string str) {
        dfs(str, 0);
        return res;
    }
    
    void dfs(string str, int x) {
        // 固定前n-1个字符，最后一个字符只有一种情况
        if (x == str.size() - 1) {
            res.push_back(str);
            return;
        }
        
        // 集合保存已固定的字符
        unordered_set<int> st;
        for (int i = x; i < str.size(); ++i) {
            // 相同字符不交换，剪枝
            if (st.find(str[i]) != st.end()) {
                continue;
            }
            st.insert(str[i]);
            // 交换字符
            swap(str[x], str[i]);
            // 当前字符已固定，固定下一个字符
            dfs(str, x + 1);
            // 恢复字符进行下一个交换
            swap(str[x], str[i]);
        }
    }
};