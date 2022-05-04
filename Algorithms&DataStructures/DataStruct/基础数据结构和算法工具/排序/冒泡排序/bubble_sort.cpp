#include <iostream>
using namespace std;

template<typename T>
void bubbleSort(T array[], int len) {
    int i, j;
    for (i = 0; i < len; ++i) {
        for (j = 0; j < len - 1; ++j) {
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

int main() {
    int array_int[] = {11, 24, 8, 32, 5, 65, 27};
    int len = (int) sizeof(array_int) / sizeof(array_int[0]);
    int i = 0;

    bubbleSort(array_int, len);
    for (i = 0; i < len; ++i) {
        cout << array_int[i] << " ";
    }
    cout << endl;
    
    return 0;
}
