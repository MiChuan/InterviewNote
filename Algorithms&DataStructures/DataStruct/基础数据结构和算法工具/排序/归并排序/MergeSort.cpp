#include<iostream>
#include<vector>
using namespace std;

void mergeSort(vector<int>& k, int n){
	int i, next, left_min, left_max, right_min, right_max;
	vector<int> temp(n);

	for(int i = 1; i < n; i *= 2){//步长, 1, 2, 4, ...
		for(left_min = 0; left_min < n - i; left_min = right_max){
			//从0开始, 根据步长, 向右分组排序
			right_min = left_max = left_min + i;
			right_max = left_max + i;
			if(right_max > n){
				right_max = n;
			}
			next = 0;
			//将k[]数组中小的数据备份
			//结束条件：left或right有一个完全拷贝到temp
			while(left_min < left_max && right_min < right_max){
				if(k[left_min] < k[right_min]){
					temp[next++] = k[left_min++];
				} else{
					temp[next++] = k[right_min++];
				}
			}
			while(left_min < left_max){
				k[--right_min] = k[--left_max];
			}
			while(next > 0){
				k[--right_min] = temp[--next];
			}
		}
	}
}

int main(){
	vector<int> array = {11, 25, 16, 2, 3, 26, 4, 91};
	cout << "array:";
	for(int tmp : array) cout << tmp << ' ';
	mergeSort(array, array.size());
	cout << endl << "sorted array: ";
	for(int tmp : array) cout << tmp << ' ';
	return 0;
}