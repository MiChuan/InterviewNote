class Solution {
public:
    vector<int> reOrderArrayTwo(vector<int>& array) {
        int i = 0, j = array.size() - 1, tmp;
        while(i < j) {
            while(i < j && (array[i] % 2) == 1) i++;
            while(i < j && (array[j] % 2) == 0) j--;
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
        return array;
    }
};