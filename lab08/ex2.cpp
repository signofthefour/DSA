#include <iostream>
#include <fstream>
using namespace std;

void HeapDown(int* arr, int N, int i) {
	while (i < N) {
		int left = i * 2 + 1;
		if (left >= N) return;
		if (left + 1 < N)
			if (arr[left] < arr[left + 1]) left++;
		if (arr[i] >= arr[left])
			return;
		swap(arr[i], arr[left]);
		i = left;
	}

}

void BuildHeap(int* arr, int N) {
	for (int i = N / 2; i > -1; i--)
		HeapDown(arr, N, i);
}

void HeapSort(int * arr, int N) {
	if (N == 1) return;
	BuildHeap(arr, N);
	swap(arr[0], arr[N - 1]);
	HeapSort(arr, N - 1);
}

void print(int* arr, int N) {
	for (int i = 0; i < N; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
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
	HeapSort(arr, N);
	print(arr, N);
	return 0;
}