#include <iostream>  
#include <fstream>
#include <list>
using namespace std;

class Adjacency
{
private:
	int* arr;
	int size;
public:
	Adjacency() {}
	Adjacency(int v) {
		arr = new int[v];
		size = 0;
	}
	void init(int v) {
		arr = new int[v];
		size = 0;
	}
	void push(int v) {
		arr[size] = v;
		size++;
	}
	void print() {
		for (int i = 0; i < size; i++) {
			cout << "-> " << arr[i];
		}
		cout << endl;
	}
	void printArray() {
		for (int i = 0; i < size - 1; i++) {
			cout << arr[i] << " ";
		}
		cout << arr[size - 1] << endl;
	}
	int getSize() {return size;}
	int getElement(int idx) {return arr[idx];}
};

class Graph
{
private:
	int V;   
	Adjacency* adj;

public:
	Graph(int V) {
		this->V = V;
		adj = new Adjacency[V];
		for (int i = 0; i < V; i++) {
			adj[i].init(V);
		}
	}

	void addEdge(int v, int w)
	{
		adj[v].push(w);
		adj[w].push(v);
	}
	
	Adjacency* BFS(int v);

	void printGraph() {
		for (int v = 0; v < V; ++v)
		{
			cout << "\nAdjacency list of vertex " << v << "\nhead ";
			adj[v].print();
		}
	}
};

Adjacency* Graph::BFS(int v)
{
	/*
	Using list<int> queue to store vertex
	Some useful method:
	- <list object>.push_back(...)
	- <list object>.front()
	- <list object>.pop_front()
	- <list object>.push_back(...)
	*/
    Adjacency* res = new Adjacency(V);
    list<int> queue;
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++) visited[i] = false;

    visited[v] = true;
    queue.push_back(v);

    while (!queue.empty()) {
        // Dequeue front from queue to adj
        v = queue.front();
        res->push(v);
        queue.pop_front();

        // Enqueue vertex connect with v
        for (int i = 0; i < adj[v].getSize(); i+=1) {
            if (!visited[adj[v].getElement(i)]) {
                queue.push_back(adj[v].getElement(i));
                visited[adj[v].getElement(i)] = true;
            }
        }
    }
    return res;
}

int main(int argc, char* argv[]) {
	ifstream inFile;
	int V, visited;

	inFile.open(argv[1]);
	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}

	inFile >> V >> visited;
	Graph g(V);
	Adjacency* arr = new Adjacency(V);
	int v, u;
	try {
		while (inFile >> u) {
			inFile >> v;
			g.addEdge(v, u);
		}
	}
	catch (char const* s) {
		printf("An exception occurred. Exception type: %s\n", s);
	}
	g.printGraph();
	arr = g.BFS(visited);
	arr->printArray();
	inFile.close();
	return 0;
}