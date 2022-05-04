class Solution {
public:
    int Add(int num1, int num2) {
        unsigned int a1 = num1, b1 = num2;
        while(b1 != 0) { // 当进位为 0 时跳出
            unsigned int c = (a1 & b1) << 1;  // c = 进位
            a1 ^= b1; // a = 非进位和
            b1 = c; // b = 进位
        }
        return a1; 
    }
};