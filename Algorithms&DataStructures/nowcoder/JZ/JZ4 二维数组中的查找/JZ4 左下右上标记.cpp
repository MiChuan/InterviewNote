class Solution {
  public:
    bool Find(int target, vector<vector<int> > array) {
        if (array.size() == 0) {
            return false;
        }

        int up = 0, left = 0;
        int down = array.size(), right = array[0].size();

        while (up < down && left < right) {
            // 下左
            if (array[down - 1][left] == target) {
                return true;
            } else if (array[down - 1][left] < target) {
                ++left;
            } else if (array[down - 1][left] > target) {
                --down;
            }

            // 上右
            if (array[up][right - 1] == target) {
                return true;
            } else if (array[up][right - 1] > target) {
                --right;
            } else if (array[up][right - 1] > target) {
                ++up;
            }
        }

        return false;
    }
};