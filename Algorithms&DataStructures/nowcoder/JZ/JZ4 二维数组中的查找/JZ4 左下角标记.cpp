class Solution {
  public:
    bool Find(int target, vector<vector<int> > array) {
        if (array.size() == 0) {
            return false;
        }

        int left = 0, down = array.size() - 1;

        while (0 <= down && left < array[0].size()) {
            // 下左
            if (array[down][left] == target) {
                return true;
            } else if (array[down][left] < target) {
                ++left;
            } else if (array[down][left] > target) {
                --down;
            }
        }

        return false;
    }
};