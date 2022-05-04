#include<iostream>
#include<vector>
using namespace std;

void quickSort(vector<int>& array, int low, int high){
	if(low >= high) return;
	int pos = low + rand() % (high - low), l = low, h = high;
	int pivot = array[pos];//基准值
	swap(array[low], array[pos]);
	while(l < h){
		while(array[h] >= pivot && l < h) --h;
		if(l < h) array[l++] = array[h];
		while(array[l] <= pivot && l < h) ++l;
		if(l < h) array[h--] = array[l];
	}
	array[l] = pivot;
	quickSort(array, low, l-1);
	quickSort(array, l+1, high);
}

int main(){
	vector<int> array = {11, 25, 16, 2, 3, 26, 4, 91};
	cout << "array:";
	for(int tmp : array) cout << tmp << ' ';
	quickSort(array, 0, array.size()-1);
	cout << endl << "sorted array: ";
	for(int tmp : array) cout << tmp << ' ';
	return 0;
}