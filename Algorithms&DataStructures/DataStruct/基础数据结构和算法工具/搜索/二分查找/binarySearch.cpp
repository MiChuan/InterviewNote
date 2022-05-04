#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

bool binarySearch(vector<int>& array, int key, int* index){
	sort(array.begin(), array.end());
	int left = 0, right = array.size()-1;
	while(left <= right){
		int mid = left + (right - left) / 2;
		if(array[mid] > key){
			right = mid -1;
		}
		else if(array[mid] < key){
			left = mid + 1;
		}
		else{
			*index = mid;
			return true;
		}
	}
	return false;
}

int main() {
	vector<int> array = {4,5,6,2,3,7};
	int index, key = 7;
	if(binarySearch(array, key, &index)) cout << "index: " << index <<endl;
	else cout << "not found" <<endl;
	return 0;
}