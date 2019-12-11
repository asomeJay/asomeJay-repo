/* graph DFS or BFS : Virus */

#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Graph {
public:
	int V;
	int count;
	list<int>* adj;

	Graph(int V);
	void add_edge(int v, int w);
	void DFS(int s);
};

Graph::Graph(int V) {
	this->V = V;
	this->adj = new list<int>[V];
	this->count = -1;
}

void Graph::add_edge(int v, int w) {
	adj[v].push_back(w);
	adj[w].push_back(v);
}

void Graph::DFS(int s) {
	bool* visited = new bool[this->V];
	int i, j, k, v;
	for (i = 0; i < this->V; i++) {
		visited[i] = false;
	}

	vector<int> stack;
	stack.push_back(s);

	list<int>::iterator it;
	while (!stack.empty()) {
		v = stack.back();
		stack.pop_back();

		if (visited[v]) 
			continue;
		cout << "v : " << v << endl;
		count++;
		visited[v] = true;
		for (it = this->adj[v].begin(); it != this->adj[v].end(); it++) {
			k = *it;
			if (!visited[(k)]) {
				stack.push_back(k);
			}
		}
	}
}

int main(void) {
	int computer_num; cin >> computer_num; // computer 개수
	int edge, i, s, v; cin >> edge; // edge 개수
	Graph g(computer_num + 1);
	for (i = 0; i < edge; i++) {
		cin >> s >> v;
		g.add_edge(s, v);
	}

	g.DFS(1);
	cout << g.count << endl;
	return 0;
}