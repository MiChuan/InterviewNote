class Solution {
public:
    string replaceSpace(string s) {
        string str;
        for(auto ch : s){
            if(ch==' ') str+="%20";
            else str+=ch;
        }
        return str;
    }
};