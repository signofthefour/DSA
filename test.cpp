#include <iostream>
#include<fstream>
using namespace std;

int main(int argv, char** argc) {
    //ifstream infile(argc[1], ios::binary);
    T* pPre = arr;
    T* pCur = arr;
    while (*pCur > key) {
        pPre = pPre->next;
        pCur = pCur->next;
        pCur = pCur->next;
    }
    //getline(cin, a);
    return 0;
}