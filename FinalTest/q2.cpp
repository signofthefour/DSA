#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <cctype>
#define FILENAME "f_g1q2_sol.cpp"
#define MAXNUMBER 1000
using namespace std;

bool codeCheck();

class MaxHeap {
private:
	int arr[MAXNUMBER];
	int count;
protected:
	int reHeapUp(int pos);
	int reHeapDown(int pos);
	static int isMaxHeapRec(int* arr, int pos, int size);

public:
	MaxHeap();
	void print();
	int* toArray();
	int getSize();

	int buildHeap(int* a, int size);
	static int isMaxHeap(int* a, int size);
};

int main(int argc, char** argv) {
	if (codeCheck() == false) {
		cout << "Forbidden-keyword rule violation." << endl;
		return -1;
	}

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

	MaxHeap* h = new MaxHeap();

	cout << n << endl;

	if (n % 2 == 0)
		cout << MaxHeap::isMaxHeap(arr, n);
	else {
		h->buildHeap(arr, n);
		cout << MaxHeap::isMaxHeap(h->toArray(), n);
	}

	ifs.close();

	return 0;
}

int MaxHeap::reHeapUp(int position) {
	if (position > 0) {
		int parent = floor((position - 1) / 2);
		if (arr[position] > arr[parent]) {
			swap(arr[position], arr[parent]);

			return 1 + reHeapUp(parent);
		}
		else return 0;
	}
	else return 0;
}

int MaxHeap::reHeapDown(int position) {
	int left = position * 2 + 1;
	int right = position * 2 + 2;
	int large = 0;
	if (left < count) {
		if (right < count && arr[right] > arr[left]) {
			large = right;
		}
		else large = left;
		if (arr[large] > arr[position]) {
			swap(arr[large], arr[position]);
			return 1 + reHeapDown(large);
		}
		else return 0;
	}
	else return 0;
}

int* MaxHeap::toArray() {
	return arr;
}

int MaxHeap::getSize() {
	return count;
}

MaxHeap::MaxHeap() {
	count = 0;
}

void MaxHeap::print() {
	for (int i = 0; i < count; i++) cout << arr[i] << " ";
	cout << endl;
}

int MaxHeap::buildHeap(int* a, int size) {
	memcpy(arr, a, size * sizeof(int));
	count = size;
	int swapCount = 0;
	for (int i = size / 2; i >= 0; i--)
		swapCount += reHeapDown(i);

	return swapCount;
}

/* Your code MUST NOT contain any words in the following list:
{"include", "while", "for", "goto"} even in the comments */

//----------------------------------------------
// Restriction area
//----------------------------------------------

int MaxHeap::isMaxHeapRec(int* arr, int pos, int size) {
    int lc = 2*pos + 1;
    if (lc >= size)
        return 1;
    int rc = lc + 1;
    if (rc >= size)
        return arr[pos] > arr[lc] ? 1 : -1;
    if (arr[pos] < arr[lc] || arr[pos] < arr[rc])
        return -1;
    int lHeap = isMaxHeapRec(arr, lc, size);
    int rHeap = isMaxHeapRec(arr, rc, size);
    if (lHeap == -1 || rHeap == -1) return -1;
    return 1 + (lHeap > rHeap ? lHeap : rHeap);
}

int MaxHeap::isMaxHeap(int* arr, int size) {
    return isMaxHeapRec(arr, 0, size);
}

bool codeCheck() {
	const char* forbiddenKeyword[] = { "include", "while", "for", "goto" };
	fstream ifs;
	ifs.open("main.cpp", ios::in);
	if (ifs.fail()) ifs.open(FILENAME, ios::in);
	if (ifs.fail()) return true;
	ifs.seekg(0, ifs.end);
	int fileSize = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	char* fileContent = new char[fileSize];
	ifs.read(fileContent, fileSize);
	ifs.close();
	*strstr(fileContent, "bool codeCheck() {") = '\0';
	char* todoSegment = strstr(fileContent, "// Restriction area");
	int numberOfForbiddenKeyword = sizeof(forbiddenKeyword) / sizeof(const char*);
	for (int i = 0; i < numberOfForbiddenKeyword; i++) { if (strstr(todoSegment, forbiddenKeyword[i])) return false; }
	delete[] fileContent;
	return true;
}
