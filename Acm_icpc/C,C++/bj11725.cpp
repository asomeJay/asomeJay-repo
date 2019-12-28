/* Graph : Find a parent of Tree! */

#include <iostream>
#include <vector>
#include <stack>
#include <list>

using namespace std;

bool visited[100001];
int depth[100001];

class DFSGraph {
	int vertex;
	list<int>* adj_list;

public:
	DFSGraph(int V) {
		int i;
		this->vertex = V;
		adj_list = new list<int>[V];
	}

	void add_edge(int v, int w) {
		this->adj_list[v].push_back(w);
		this->adj_list[w].push_back(v);
	}

	void make_depth();
	void DFS_parent(int);
};

void DFSGraph::make_depth() {
	int v = 1;
	stack<int> s;

	s.push(v);

	while (!s.empty()) {
		v = s.top();
		s.pop();
		visited[v] = true;
		list<int>::iterator i;
		for (i = this->adj_list[v].begin(); i != this->adj_list[v]
			.end(); i++) {
			if (!visited[*i]) {
				depth[*i] = v;

				s.push(*i);
			}
		}
	}

	

}

void DFSGraph::DFS_parent(int v) {
	printf("%d\n", depth[v]);
}

int main(void) {
	int n_of_node, i, j, s_v, f_v; 
	scanf("%d", &n_of_node);

	DFSGraph g_dfs(n_of_node + 1);

	for (i = 1; i <= n_of_node - 1; i++) {
		scanf("%d %d", &s_v, &f_v);
		g_dfs.add_edge(s_v, f_v);
	}

	g_dfs.make_depth();

	for (i = 2; i <= n_of_node; i++) 
		g_dfs.DFS_parent(i);
	
	

	return 0;
}