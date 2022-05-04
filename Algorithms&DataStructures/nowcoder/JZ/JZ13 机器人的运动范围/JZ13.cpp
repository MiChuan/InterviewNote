class Solution {
  public:
    int movingCount(int threshold, int rows, int cols) {
        vector<vector<bool>> visited(rows, vector<bool>(cols, 0));
        return dfs(0, 0, 0, 0, visited, rows, cols, threshold);
    }
    int dfs(int i, int j, int si, int sj, vector<vector<bool>>& visited, int m, int n, int k) {
        if (i >= m || j >= n || k < si + sj || visited[i][j]) return 0;
        visited[i][j] = true;
        return 1 + dfs(i + 1, j, (i + 1) % 10 != 0 ? si + 1 : si - 8, sj, visited, m, n, k) +
               dfs(i, j + 1, si, (j + 1) % 10 != 0 ? sj + 1 : sj - 8, visited, m, n, k);
    }
};