class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        int i = 0, min = rotateArray[0];
        
        for (i = 0; i < rotateArray.size(); ++i) {
            min = min > rotateArray[i] ? rotateArray[i] : min;
        }
        
        return min;
    }
};