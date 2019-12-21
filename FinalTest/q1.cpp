#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <cctype>
#define THRESHOLD 10
using namespace std;

void insertionSort(int* arr, int low, int high) {
	cout << "Insertion Sorting Call" << endl;

    for (int j = low; j <= high; j++) {
        int key = arr[j];
        for (int i = j; i >= 1; i--) {
            if (key < arr[i - 1]) {
                arr[i] = arr[i - 1];
            }
            else {
                arr[i] = key;
                break;
            }
        }
        if (arr[0] > key) arr[0] = key; 
    }
}

int partition(int* arr, int low, int high) {

}


void hybridSortUtil(int* arr, int low, int high) {
    int lower = low + 1, upper = high;
    int bound = arr[lower];
    while (lower <= upper) {
        while (bound > arr[lower])
            lower++;
        while (bound < arr[upper])
            upper--;
        if (lower < upper) {
            swap(arr[lower++], arr[upper--]);
        }
        else {
            lower++;    
        }
    }
    swap(arr[lower], arr[upper]);
    if (high > upper + 1)
        hybridSort(arr, high - upper);
    if (low < upper - 1)
        hybridSort(arr, upper - lower);
}

void hybridSort(int* arr, int size) {
	if (size < THRESHOLD) {
        insertionSort(arr, 0, size  -1);
    } else {
        hybridSortUtil(arr, 0, size - 1);
    }
}

int main(int argc, char** argv) {
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);

	string temp;
	getline(ifs, temp);

	int n = stoi(temp);
	int* arr = new int[n];

	for (int i = 0; i < n; i++) {
		getline(ifs, temp);
		arr[i] = stoi(temp);
	}

	if (n % 2 == 0) {
		insertionSort(arr, 1, n - 3);
	}
	else hybridSort(arr, n);

	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}

	ifs.close();

	return 0;
}
