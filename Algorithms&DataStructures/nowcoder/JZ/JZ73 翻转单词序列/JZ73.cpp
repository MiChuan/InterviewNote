class Solution {
public:
    stack<char> chstack;
    
    string ReverseSentence(string str) {
        string res = "";
        int i = str.size() - 1;
        
        // 跳过尾部空格
        while (i >= 0 && ' ' == str[i]) {     
            --i;
        }
        
        while(i >= 0) {
            // 非空格字符进栈
            if (' ' != str[i]) {
                chstack.push(str[i]);
            } else {
                // 读到空格字符出栈
                while (!chstack.empty()) {
                    res += chstack.top();
                    chstack.pop();
                }
            }
            
            // 跳过中间多余空格
            // 读到下一个单词，字符串加空格
            if(' ' != str[i] &&
               ' ' == str[i + 1]) {
                res += ' ';
            }
            
            --i;
        }
        
        // 最后一个单词
        while (!chstack.empty()) {
            res += chstack.top();
            chstack.pop();
        }
        
        return res;
    }
};

// "   abc   "
// "ab    cdef"
//"fedc ba"
//"cdef ab"