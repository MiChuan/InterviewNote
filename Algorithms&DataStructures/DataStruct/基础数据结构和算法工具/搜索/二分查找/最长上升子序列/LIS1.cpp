#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> getdp2(vector<int> &arr);
vector<int> generateLIS(vector<int> &arr, vector<int>&dp);

int main() {
	vector<int> arr = {4,5,6,2,3,7};
/*
    int temp;
    while(cin >> temp){
        arr.push_back(temp);
    }
*/
	vector<int> dp = getdp2(arr);
	vector<int> lis = generateLIS(arr, dp);
	for (int i = 0; i < lis.size(); i++){
		cout << lis[i]<<" ";
	}
	return 0;
}

vector<int> getdp2(vector<int> &arr){
	vector<int> dp(arr.size(), 0);
	vector<int> ends(arr.size(), 0);
	ends[0] = arr[0]; dp[0] = 1;
	int right = 0; int l = 0; int r = 0; int m = 0;
	for (int i = 1; i < arr.size(); i++) {
		l = 0;
		r = right;
		while(l <= r){//二分法
		m = (l + r) / 2;
		if (arr[i] > ends[m]){
			l = m + 1;
			}else {
				r = m - 1;
			}
		}
		right = max(right, l);
		ends[l] = arr[i];
		dp[i] = l + 1;
		}
	return dp;
}

vector<int> generateLIS(vector<int> &arr, vector<int> &dp){
	int len = 0; int index = 0;
	for (int i = 0; i < dp.size(); i++) { //寻最长递增子序列末尾的位置和值
		if (dp[i] > len) {
			len = dp[i];
			index = i;
		}
	}
	vector<int> lis(len, 0);
	lis[--len] = arr[index];
	for (int i = index; i >= 0; i--){
		if(arr[i] < arr[index] && dp[i] == dp[index] - 1){//从后往前找子序列
			lis[--len] = arr[i];
			index = i;
		}
	}
	return lis;
}
/* input
4 5 6 2 3 7
*/
/* output
4 5 6 7
*/