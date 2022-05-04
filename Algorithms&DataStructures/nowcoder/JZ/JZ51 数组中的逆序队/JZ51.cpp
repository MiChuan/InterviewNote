class Solution {
public:
    int reversePairs(vector<int>& nums) {
        vector<int> tmp(nums.size());
        return mergeSort(0, nums.size() - 1, nums, tmp);
    }

    int mergeSort(int left, int right, vector<int> &data, vector<int> &tmp) {
        if (left >= right) return 0;
        int mid = (left + right) / 2;
        int res = mergeSort(left, mid, data, tmp) + mergeSort(mid + 1, right, data, tmp);
        int i = left, j = mid + 1, k;
        
        for (k = left; k <= right; ++k) {
            tmp[k] = data[k];
        }
        
        for (k = left; k <= right; ++k) {
            if (mid + 1 == i) {
                // 左边数组元素合并完毕，剩下右边元素
                data[k] = tmp[j];
                ++j;
            }
            else if (right + 1 == j || tmp[i] <= tmp[j]) {
                // 右边数组元素合并完毕
                // 或未合并完毕，左边元素小放在前面
                data[k] = tmp[i];
                ++i;
            }
            else {
                // 未合并完毕，右边元素小
                // 左边元素大于右边，逆序对
                res += mid - i + 1;
                data[k] = tmp[j];
                ++j;
            }
        }
        
        return res;
    }
};