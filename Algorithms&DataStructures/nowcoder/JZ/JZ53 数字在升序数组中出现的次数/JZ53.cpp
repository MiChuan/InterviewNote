class Solution {
public:
    int GetNumberOfK(vector<int> data ,int k) {
        int i = 0, count = 0;
        
        for(i = 0; i < data.size(); ++i) {
            if (data[i] == k) {
                ++count;
            }
            else if (data[i] > k) {
                break;
            }
        }
        
        return count;
    }
};