class Solution {
public:
    double Power(double base, int exponent) {
        if(base == 0) return 0;//底数为0
        long b = exponent;//记录二进制位
        double res = 1.0;
        if(b < 0) {//幂指数为负数
            base = 1 / base;
            b = -b;
        }
        while(b > 0) {//遍历幂指数二进制位
            if((b & 1) == 1) res *= base;//各二进制位指数运算结果相乘
            base *= base;//计算各二进制位指数基
            b >>= 1;
        }
        return res;
    }
};