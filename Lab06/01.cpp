#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <string.h>
#include <time.h>

using namespace std;

template <typename T>
class node
{
public:
    T data;
    node<T> *left = NULL;
    node<T> *right = NULL;
    int balance = 0;
    node(T data)
    {
        this->data = data;
    };
    // you can implement other relevant things here
    int     height = 0;
    getBalance(){return balance;}
    getHeight(){return height;}
};

template <typename T>
class AVLtree
{
    node<T> *root = NULL;
    // you can implement other relevant things here
    node* rightRotate(node* y) {
        node* x = y->left;
        node* T2 = x->right;
        // Rotate
        x->right = y;
        y->left = T2;
        // Update heights
        x->height =  x->left->getHeight() > x->right->getHeight() + 1? x->left->getHeight() : x->right->getHeight() + 1;
    }
    void print(node<T> *&subroot)    {
        if (subroot == 0)
        {
            cout << '*';
            return;
        }
        cout << subroot->data;
        cout << '(';
        print(subroot->left);
        cout << '|';
        print(subroot->right);
        cout << ')';
        return;
    }

public:
    AVLtree() {}

    // the add function:
    bool add(T &data)
    {
        
    }

    void print()
    {
        print(root);
    }
};


int main(int argc, char* argv[]) {
    ifstream inFile;
	int i;
	inFile.open(argv[1]);
	AVLtree<int> *a=new AVLtree<int>;

	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}
	while(inFile>>i){
		a->add(i);
	}
    a->print();
	inFile.close();
	return 0;
}