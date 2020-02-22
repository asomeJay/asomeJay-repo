/* 특정한 최단거리 */

#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <climits>
#include <vector>

#define MAXNODE 800 + 1
#define UNVISIT 0
#define VISIT 1
#define INF 987654321

using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pi;

struct cmp {
	bool operator()(pi a, pi b) {
		return a.second < b.second;
	}
};

vector<pair<int,int>> edge[MAXNODE];

int n_of_node, n_of_edge;
int must_a, must_b;

ll dijkstra(int start, int end);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> n_of_node >> n_of_edge;
	int i, j, a, b, c;
	for (i = 1; i <= n_of_edge; i++) {
		cin >> a >> b >> c;
		edge[a].push_back(make_pair(b, c));
		edge[b].push_back(make_pair(a, c));
	}
	cin >> must_a >> must_b;
	// 1. 1 -> must_a -> must_b -> n_of_node
	ll middle = dijkstra(must_a, must_b);
	ll dfs_a = dijkstra(1, must_a) + middle + dijkstra(must_b, n_of_node);
	// 2. 1 -> must_b -> must_a -> n_of_node
	ll dfs_b = dijkstra(1, must_b) + middle + dijkstra(must_a, n_of_node);
	ll result;

	if (dfs_a >= INF || dfs_b >= INF) 
		result = -1;
	else
		result = min(dfs_a, dfs_b);
	cout << result;

	return 0;
}

ll dijkstra(int start, int end) {
//	cout << "start : " << start << " end : " << end << endl;
	priority_queue<pi, vector<pi>, cmp> p_q;
	ll i, node, node_value;
	vector<ll> distance(n_of_node+1, INF);
	distance[start] = 0;

	p_q.push(make_pair(start, 0));

	while (!p_q.empty()) {
		
		node = p_q.top().first;
		node_value = p_q.top().second;
//		cout << " node : " << node << " node_value : "<< node_value <<endl;

		p_q.pop();

		int node_size = edge[node].size();
		
		for (i = 0; i < node_size; i++) {
			int target = edge[node][i].first;
			ll new_target_value = node_value + edge[node][i].second;
			if (distance[target] > new_target_value) {
				distance[target] = new_target_value;
				p_q.push(make_pair(target, new_target_value));
			}
		}
	}

	return distance[end];

}