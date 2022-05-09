#include<iostream>
#include<vector>
using namespace std;

int getIndex(vector<int>& array, int low, int high){
    int pos = low + rand() % (high - low);
    int pivot = array[pos]; //基准值
    swap(array[pos], array[low]);
	while(low < high){
		while (low < high && array[high] >= pivot){
			high--;
		}
		// 如果队尾元素小于tmp了,需要将其赋值给low
		array[low] = array[high];
		// 当队首元素小于等于tmp时,向前挪动low指针
		while (low < high && array[low] <= pivot) {
			low++;
		}
		// 当队首元素大于tmp时,需要将其赋值给high
		array[high] = array[low];
	}
	array[low] = pivot;
	return low;
}

void quickSort(vector<int>& array, int low, int high){
	if(low < high){
		int index = getIndex(array, low, high);
		quickSort(array, low, index-1);
		quickSort(array, index+1, high);
	}
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