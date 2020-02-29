/* 타임머신 */

#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_MAP 501
#define INF 987654321

using namespace std;

int city, bus;
vector<pair<int, int>> route[MAX_MAP];

int dist[MAX_MAP];

bool bellman_ford();

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> city >> bus;

	for (int i = 1, a, b, c; i <= bus; i++) {
		cin >> a >> b >> c;
		route[a].push_back({ b,c });
	}

	if (bellman_ford()) {
		cout << -1 << '\n';
	} else {
		for (int i = 2; i <= city; i++) {
			if (dist[i] != INF)
				cout << dist[i] << '\n';
			else
				cout << -1 << '\n';
		}
	}
	return 0;
}

bool bellman_ford() {
	bool cycle = false;
	for (int i = 1; i <= city; i++) 
		dist[i] = INF;
	
	dist[1] = 0;

	for (int i = 1; i <= city; i++) {
		for (int j = 1; j <= city; j++) {
			for (auto &n : route[j]) {
				if (dist[j] != INF && (dist[n.first] > dist[j] + n.second)) {
					dist[n.first] = dist[j] + n.second;
					if (i == city) cycle = true;
				}
			}
		}
	}
	return cycle;
}