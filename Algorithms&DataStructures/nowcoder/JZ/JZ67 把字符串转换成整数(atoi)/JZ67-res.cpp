class Solution {
public:
    int StrToInt(string str) {
        int i = 0, j = 0, res = 0, sign = 1, len = str.size();
        int const bound = INT_MAX / 10;               //INT_MAX == 2147483647
        for (i = 0; i < len && str[i] == ' '; ++i) {} //跳过空格
        if (str[i] == '-') sign = -1;                 //跳过符号位
        if (str[i] == '-' || str[i] == '+') ++i;
        for (j = i; j < len; ++j) {
            if ('0' > str[j] || str[j] > '9') break;  //非数字
            else if (res > bound || (res == bound && str[j] > '7')) {
                return 1 == sign ? INT_MAX : INT_MIN; //数字范围越界
            }
            else {
                res = res * 10 + (str[j] - '0');
            }
        }
        return sign * res;
    }
};