#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <cctype>
#define FILENAME "f_g1q1_sol.cpp"
using namespace std;

bool codeCheck();

class Node {
public:
	int data;
	Node* left;
	Node* right;

	Node(int val) {
		data = val;
		left = right = NULL;
	}
};

class BinaryTree
{
private:
	Node * root;
	int size;
	string* arr;
	int arrSize;

protected:
	void clearRecursion(Node*root);
	void addBSTRecursion(Node*& root, int val);
	int getHeightRecursion(Node* root);
	bool isBalancedRecursion(Node* root);
	void traverseInRequirementRecursion(Node* root, int distance);
	void setSizeForArr(int newSize);

public:
	BinaryTree();
	~BinaryTree();
	void clear();
	void addBST(int val);
	int getHeight();
	bool isBalanced();
	void traverseInRequirement();
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

	BinaryTree* tree = new BinaryTree();
	for (int i = 0; i < n; i++) {
		tree->addBST(arr[i]);
	}

	if (n % 2 == 0) {
		cout << tree->isBalanced();
	}
	else tree->traverseInRequirement();

	ifs.close();

	// system("pause");
	return 0;
}

BinaryTree::BinaryTree()
{
	root = NULL;
	size = 0;
	arrSize = 100;
	arr = new string[arrSize];

	for (int i = 0; i < arrSize; i++) {
		arr[i] = "";
	}
}

BinaryTree::~BinaryTree()
{
	clear();
}

void BinaryTree::setSizeForArr(int newSize) {
	if (newSize > this->arrSize) {
		string* newStorage = new string[newSize];
		for (int i = 0; i < newSize; i++) {
			newStorage[i] = "";
		}
		memcpy(newStorage, arr, sizeof(string)* arrSize);
		arrSize = newSize;
		delete arr;
		arr = newStorage;
	}
}


void BinaryTree::clearRecursion(Node* root) {
	if (root != NULL) {
		clearRecursion(root->left);
		clearRecursion(root->right);
		delete root;
	}
}
void BinaryTree::clear() {
	clearRecursion(root);
}

void BinaryTree::addBSTRecursion(Node*& root, int val) {
	if (root == NULL)
		root = new Node(val);
	else {
		if (val > root->data)
			addBSTRecursion(root->right, val);
		else
			addBSTRecursion(root->left, val);
	}
}

void BinaryTree::addBST(int val) {
	addBSTRecursion(root, val);
}

/* Your code MUST NOT contain any words in the following list:
{"include", "while", "for", "goto"} even in the comments */

//----------------------------------------------
// Restriction area
//----------------------------------------------

int BinaryTree::getHeightRecursion(Node* root) {
    if (root == NULL) return 0;
    int lH = getHeightRecursion(root->left);
    int rH = getHeightRecursion(root->right);
    return 1 + (lH > rH ? lH : rH);
}

int BinaryTree::getHeight() {
    return getHeightRecursion(root);
}

bool BinaryTree::isBalancedRecursion(Node* root)
{
    if (root == NULL) return true;
    int lH = getHeightRecursion(root->left);
    int rH = getHeightRecursion(root->right);
    bool res =  (lH == rH) || (lH==rH - 1) || (lH = rH - 1);
    bool lB = isBalancedRecursion(root->left);
    bool rB = isBalancedRecursion(root->right);
    return res && lB && rB;
}

bool BinaryTree::isBalanced() {
    return isBalancedRecursion(root);
}

void BinaryTree::traverseInRequirementRecursion(Node* root, int distance) {
    if (root == NULL) return ;
    setSizeForArr(distance + 1);
    if (arr[distance] != "") arr[distance] += " " + to_string(root->data);
    else arr[distance] += to_string(root->data);
    traverseInRequirementRecursion(root->left, distance + 1);
    traverseInRequirementRecursion(root->right, distance);
}

void BinaryTree::traverseInRequirement() {
    traverseInRequirementRecursion(root, 0);
    for(int i = 0; i < arrSize; i++) {
        if (arr[i] != "")
            cout << arr[i] << '\n';
    }
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