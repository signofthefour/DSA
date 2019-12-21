#include <iostream>
#include <fstream>
using namespace std;

void swap(int& a, int& b) {
    int c = a;
    a = b;
    b = c;
}

void QuickSort(int data[], int first, int last) {
    int lower = first + 1, upper = last;
    int bound = data[first];
    while (lower <= upper) {
        while (bound > data[lower])
            lower++;
        while (bound < data[upper])
            upper--;
        if (lower < upper) {
            swap(data[lower++], data[upper--]);
        }
        else {
            lower++;
        }
    }
    swap(data[first], data[upper]);
    if (last > upper + 1)
        QuickSort(data, upper + 1, last);
    if (first < upper - 1)
        QuickSort(data, first, upper - 1);
}

void QuickSort(int arr[], int N) {
    int i, max, c;
    if ( N < 2)
        return;
    for (i = 1, max = 0; i < N; i++) {
        if (arr[max] < arr[i])
            max = i;
    }
    swap(arr[N - 1], arr[max]);
    QuickSort(arr, 0, N - 2);
}

void print(int* arr, int N) {
	for (int i = 0; i < N; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1];
    int R[n2];
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    // int i, j, k; 
    // int n1 = m - l + 1; 
    // int n2 =  r - m; 
  
    // /* create temp arrays */
    // int L[n1], R[n2]; 
  
    // /* Copy data to temp arrays L[] and R[] */
    // for (i = 0; i < n1; i++) 
    //     L[i] = arr[l + i]; 
    // for (j = 0; j < n2; j++) 
    //     R[j] = arr[m + 1+ j]; 
  
    // /* Merge the temp arrays back into arr[l..r]*/
    // i = 0; // Initial index of first subarray 
    // j = 0; // Initial index of second subarray 
    // k = l; // Initial index of merged subarray 
    // while (i < n1 && j < n2) 
    // { 
    //     if (L[i] <= R[j]) 
    //     { 
    //         arr[k] = L[i]; 
    //         i++; 
    //     } 
    //     else
    //     { 
    //         arr[k] = R[j]; 
    //         j++; 
    //     } 
    //     k++; 
    // } 
  
    // /* Copy the remaining elements of L[], if there 
    //    are any */
    // while (i < n1) 
    // { 
    //     arr[k] = L[i]; 
    //     i++; 
    //     k++; 
    // } 
  
    // /* Copy the remaining elements of R[], if there 
    //    are any */
    // while (j < n2) 
    // { 
    //     arr[k] = R[j]; 
    //     j++; 
    //     k++; 
    // } 
}

void MergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MergeSort(arr, left, mid);
        MergeSort(arr, mid + 1,  right);
        merge(arr, left, mid, right);
    }
}

void MergeSort(int arr[], int N) {
    MergeSort(arr, 0, N - 1);
}

int main(int argc, char* argv[]) {
	ifstream ifs;
	int i = 0;
	int N;
	
	ifs.open(argv[1]);
	if (!ifs) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}
	ifs >> N;
	int* arr = new int[N];
	while (ifs >> arr[i]) {
		i++;
	}
	MergeSort(arr, N);
	print(arr, N);
	return 0;
}