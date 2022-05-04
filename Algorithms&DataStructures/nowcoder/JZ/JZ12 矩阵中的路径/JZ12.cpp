class Solution {
  public:
    bool hasPath(vector<vector<char> >& matrix, string word) {
        int row = 0, col = 0;
        for (row = 0; row < matrix.size(); ++row) {
            for (col = 0; col < matrix[0].size(); ++col) {
                if (dfs(matrix, word, row, col, 0)){
                    return true;
                }
            }
        }
        return false;
    }

    bool dfs(vector<vector<char>>& matrix, string& word, int row, int col, int strIndex){
        if(row >= matrix.size() || row < 0 || col >= matrix[0].size() || 
            col < 0 || matrix[row][col] != word[strIndex]) return false;//越界或不匹配
        if(strIndex + 1 == word.size()) return true;//匹配完毕
        
        char tmp = matrix[row][col];//标记已检索
        matrix[row][col] = '/';
        bool res = dfs(matrix, word, row+1, col, strIndex+1) || 
            dfs(matrix, word, row-1, col, strIndex+1) ||
            dfs(matrix, word, row, col+1, strIndex+1) ||
            dfs(matrix, word, row, col-1, strIndex+1);//检索当前位置下上右左与下一个字符是否匹配
        matrix[row][col] = tmp;//恢复标记字符
        return res;
    }
};