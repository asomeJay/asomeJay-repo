/* DFS 문제 : 연결요소 찾기 */

#include <iostream>
#include <list>

using namespace std;

class Graph {

	int V;
	int count;
	list <int>* adj;
	
	void DFSUtil(int v, bool visited[]);

public:
	Graph(int V);
	void addEdge(int v, int w);
	void connectedComponents();
	void print_count();
};


void Graph::print_count() {
	cout << count << endl;
}
void Graph :: connectedComponents() {
	int i, j, v;
	bool* visited = new bool[this->V];

	for (v = 0; v < this->V; v++)
		visited[v] = false;

	for (v = 0; v < this->V; v++) {
		if (visited[v] == false) {
			DFSUtil(v, visited);
			this->count++;
//			cout << endl;
		}
	}
}

void Graph::DFSUtil(int v, bool visited[]) {
	visited[v] = true;
//	cout << v << " ";

	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); i++) {
		if (!visited[*i])
			DFSUtil(*i, visited);
	}
}

Graph::Graph(int V) {
	this->V = V;
	adj = new list<int>[V];
	this->count = 0;
}

void Graph::addEdge(int v, int w) {
	adj[v].push_back(w);
	adj[w].push_back(v);
}

int main(void) {
	int vertex, edge, i, j;
	int ver1, ver2;
	cin >> vertex >> edge;

	Graph h(vertex);

	for (i = 0; i < edge; i++) {
		cin >> ver1 >> ver2;
//		cout << "ver:: " << ver1 << " " << ver2 << endl;
		h.addEdge(ver1-1, ver2-1);
	}
	h.connectedComponents();
	h.print_count();
	return 0;
}