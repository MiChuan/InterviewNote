class Solution {
public:
     int NumberOf1(int n) {
         unsigned int x = n, i = 0;
         while (x > 0) {
             if (x & 0x1) {
                 ++i;
             }
             x >>= 0x1;
         }
         return i;
     }
};