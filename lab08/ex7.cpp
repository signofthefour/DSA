#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<list>
using namespace std; 

class Graph 
{ 
	int V; 

	list<int> *adj; 

	vector<int> indegree; 

	void alltopologicalSortUtil(vector<int>& res, bool visited[]); 

public: 
	Graph(int V); 

	void addEdge(int v, int w); 

	void alltopologicalSort(); 
    Graph(){
        V = 0;
        adj = NULL;
    } 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new list<int>[V]; 

	for (int i = 0; i < V; i++) 
		indegree.push_back(0); 
} 

void Graph::addEdge(int v, int w) 
{ 
	adj[v].push_back(w); 

	indegree[w]++; 
} 

void Graph::alltopologicalSortUtil(vector<int>& res, bool visited[]) 
{ 
    // TODO: <res> variables should contain the topology order after each step
    // TODO: Depth first search to calculate the finished time of each vertex
    //          insert which finished in front of res
    // FIXME: If use recursion, it will not synchronous 
	bool flag = false;

    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0 && !visited[i]) {
			// Exe this vertex
			// Decreasing the indegree of all child of this v
			list<int> :: iterator j;
			for (j = adj[i].begin(); j != adj[i].end(); j++) {
				indegree[*j]--;
			}
			// Push to the res and visit this
			res.push_back(i);
			visited[i] = true;
			alltopologicalSortUtil(res, visited);

			// Backtrack and reset
			visited[i] = false;
			res.erase(res.end()  - 1);
			for (j = adj[i].begin(); j != adj[i].end(); j++) {
				indegree[*j]++;
			}

			flag = true;
		}
    }

	if (!flag) {
		for (int i = 0; i < res.size(); i++) {
			cout << res[i] << ' ';
		}
		cout << '\n';
	}
} 

void Graph::alltopologicalSort() 
{ 
	bool *visited = new bool[V]; 
	for (int i = 0; i < V; i++) 
		visited[i] = false; 

	vector<int> res; 
	alltopologicalSortUtil(res, visited); 
} 

int main(int argc, char** argv) 
{ 
	ifstream inFile;
    string input;
    
    inFile.open(argv[1]);

    if(!inFile)
	{
        cout<<"Unable to open file"<<endl;
        exit(1);
    }

	Graph g; 
    int numNodes;
	int count = 0;
	while (getline(inFile, input)) 
	{
		if(count == 0) {numNodes = stoi(input); g = (numNodes); count++; continue;}
		stringstream s(input);
		int src, dst;
		s >> src >> dst;
        g.addEdge(src, dst);
	}

	cout << "All Topological sorts\n"; 

	g.alltopologicalSort(); 

	return 0; 
}