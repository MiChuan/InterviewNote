class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param numbers int整型vector 
     * @return int整型
     */
    int duplicate(vector<int>& numbers) {
        unordered_set<int> s;
        for (int temp : numbers) {
            if (temp < numbers.size() && temp >=0 &&
               temp <= 10000) {
                if (s.find(temp) != s.end()) {
                    return temp;
                }
                else {
                    s.insert(temp);
                }
            }
            else {
                break;
            }
        }
                
        return -1;
    }
};