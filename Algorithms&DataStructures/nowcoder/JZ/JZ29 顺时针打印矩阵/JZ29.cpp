class Solution {
  public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
        vector<int> out;
        if (matrix.size() == 0) return out;
        int left = 0, right = matrix[0].size() - 1;
        int top = 0, bottom = matrix.size() - 1;
        int i = 0, j = 0;

        while (true) {
            for (i = top, j = left; j <= right; ++j) {
                out.push_back(matrix[i][j]);
            }
            if (++top > bottom) break;
            
            for (i = top, j = right; i <= bottom; ++i) {
                out.push_back(matrix[i][j]);
            }
            if (--right < left) break;
            
            for (i = bottom, j = right; left <= j; --j) {
                out.push_back(matrix[i][j]);
            }
            if (--bottom < top) break;
            
            for (i = bottom, j = left; top <= i; --i) {
                out.push_back(matrix[i][j]);
            }
            if (++left > right) break;
        }

        return out;
    }
};