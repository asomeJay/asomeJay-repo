/* 최스 스패닝 트리 */

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_VERTEX 10001
#define MAX_EDGE 100001
#define SAME -1
#define DIFF -2

using namespace std;

class node {
public:
	int v, e, w;
	node(int a, int b, int c) {
		this->v = a;
		this->e = b;
		this->w = c;
	}
};

bool comp(const node& a, const node& b) {
	return a.w < b.w;
}

int V, E;
int parent[MAX_VERTEX];

int find_parent(int);
int union_node(int, int);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	vector<node> node_map;
	cin >> V >> E;
	int t_a, t_b, t_c;
	for (int i = 1; i <= E; i++) {
		cin >> t_a >> t_b >> t_c;
		node_map.push_back(node(t_a, t_b, t_c));
	}

	for (int i = 1; i <= V; i++) 
		parent[i] = i;
	
	sort(node_map.begin(), node_map.end(), comp);
	int par_a, par_b, ans_node;
	ans_node = 0;
	for (int i = 0; i < node_map.size(); i++) {
		par_a =  find_parent(node_map[i].v);
		par_b = find_parent(node_map[i].e);

		if (par_a == par_b)
			continue;
		ans_node += node_map[i].w;

		union_node(par_a, par_b);
	}
	cout << ans_node << '\n';
	return 0;
}

int find_parent(int child) {
	if (child == parent[child]) return child;
	return parent[child] = find_parent(parent[child]);
}

int union_node(int a, int b) {
	int parent_a = find_parent(a);
	int parent_b = find_parent(b);

	parent[a] = parent_b;
	find_parent(a);
	return 0;
}