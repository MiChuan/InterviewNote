class Solution {
public:
    /*
     * 回溯函数
     * 使用set函数对字符串字符进行去重，
     * 使用swap函数交换两个字符
     * */
    void backtrack(std::string s, int start, std::set<std::string> &res) {
        // 回溯结束条件
        if(start == s.size()){
            res.insert(s);
            return;
        }

        for(int i = start; i < s.size(); i++){
            // 做选择
            std::swap(s[i], s[start]);
            // 进入下一次决策树
            backtrack(s, start+1, res);
            // 撤销选择
            std::swap(s[i], s[start]);
        }
    }
    
    vector<string> Permutation(string str) {
        // 去重处理
        std::set<std::string> res;
        backtrack(str, 0, res);

        return std::vector<std::string>(res.begin(), res.end());
    }
};