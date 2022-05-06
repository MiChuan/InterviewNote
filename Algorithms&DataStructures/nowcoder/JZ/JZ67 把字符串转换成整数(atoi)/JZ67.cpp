class Solution {
public:
    int StrToInt(string str) {
        if(str.empty()) return 0;
        long num = 0;
        int sign = 1;
        int digit = 0;
        int i = 0;
        while(i<str.size() && str[i] == ' '){//跳过空格
            i++;
        }
        if(i!=str.size()){
            if('0'<=str[i] && str[i]<='9'){//以数字开头
                while(i<str.size() && '0'<=str[i] && str[i]<='9'){
                    digit = str[i] - '0';
                    num = num*10 + digit;
                    if(num > INT_MAX) return INT_MAX;
                    i++;
                }
                return num;
            }
            else if(str[i] == '-' || str[i] == '+'){//以正负号开头
                if(str[i] == '-'){
                    sign = -1;
                    i++;
                    while(i<str.size() && '0'<=str[i] && str[i]<='9'){
                        digit = str[i] - '0';
                        num = num*10 + digit;
                        if(sign*num < INT_MIN) return INT_MIN;
                        i++;
                    }
                } 
                else{
                    i++;
                    while(i<str.size() && '0'<=str[i] && str[i]<='9'){
                        digit = str[i] - '0';
                        num = num*10 + digit;
                        if(num > INT_MAX) return INT_MAX;
                        i++;
                    }
                }
                return sign * num;
            }
        }
        return 0;
    }
};