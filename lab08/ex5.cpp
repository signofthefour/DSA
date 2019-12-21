#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

void insertionSort(int arr[], int start, int end){
    if (start > end) return;
    int key = arr[start];
    for (int i = start; i >= 1; i--) {
        if (key < arr[i - 1]) {
            arr[i] = arr[i - 1];
        }
        else {
            arr[i] = key;
            break;
        }
    }
    if (arr[0] > key) arr[0] = key; 
    insertionSort(arr, start + 1, end);
}

void printArr(int arr[], int size){
    for(int i = 0; i < size; i++){
        cout<< arr[i] << " ";
    }
    cout<< endl;
}

int main(int argc, char** argv){
    ifstream inFile;
    string input;
    
    inFile.open(argv[1]);

    if(!inFile){
        cout<<"Unable to open file"<<endl;
        exit(1);
    }

    vector<string> num;
    int count = 0;
	while (getline(inFile, input, ',')){
		num.push_back(input);
	}

    int size = num.size();
    int* arr = new int[size];
    for (auto i = num.begin(); i != num.end(); i++){
		arr[count] = stoi(*i);
        count++;
	}
    insertionSort(arr, 0, size - 1);
    printArr(arr, size);

    return 0;
}