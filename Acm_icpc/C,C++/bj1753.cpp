/* 최단경로 */

#include <iostream>
#include <vector>
#include <queue>

#define INF 123456789
#define V_MAX 20001
#define E_MAX 300001

using namespace std;

int dist[V_MAX];
vector<pair<int, int>> adj[V_MAX];

void dijkstra(int s_v);

int main(void) {
	int i, j;
	int v, e, s_v, n_v, n_e, n_w;
	scanf("%d %d", &v, &e);
	scanf("%d", &s_v);

	for (i = 1; i <= v; i++) 
		dist[i] = INF;
	
	for (i = 1; i <= e; i++) {
		scanf("%d %d %d", &n_v, &n_e, &n_w);
		adj[n_v].push_back(make_pair(n_e, n_w));
	}

	dijkstra(s_v);

	for (i = 1; i <= v; i++) {
		if (dist[i] == INF)
			printf("INF\n");
		else 
			printf("%d\n", dist[i]);
	}

	return 0;
}

void dijkstra(int s_v) {
	int k;
	int n, w, new_val, before_val;
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

	dist[s_v] = 0; 
	pq.push(make_pair(dist[s_v], s_v));

	while (!pq.empty()) {
		n = pq.top().second;
		w = pq.top().first;
		pq.pop();

		for (k = 0; k < adj[n].size(); k++) {
			new_val = dist[n] + adj[n][k].second;
			before_val = dist[adj[n][k].first];

			if (new_val < before_val) {
				dist[adj[n][k].first] = new_val;
				pq.push(make_pair(new_val, adj[n][k].first));
				//pq.push(make_pair(adj[n][k].second,new_val));
			}
		}
	}

}