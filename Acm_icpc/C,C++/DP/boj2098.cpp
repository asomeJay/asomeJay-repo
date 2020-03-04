/* 외판원 순회 */

#include <iostream>
#include <algorithm>

#define MAX 987321654

using namespace std;

int dist[16][1 << 16];
int weight[16][16];
int n_of_city;

int circular(int cur, int visited);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n_of_city;
	for (int i = 0; i < n_of_city; i++) {
		for (int j = 0; j < n_of_city; j++) {
			cin >> weight[i][j];
		}
	}
	cout << circular(0, 1) << '\n';

	return 0;
}

int circular(int cur, int visited) {
	if (visited == ((1 << n_of_city) - 1)) {
		return weight[cur][0];
	}

	int ret = dist[cur][visited];
	if (ret != 0) return ret;

	ret = MAX;
	for (int i = 0; i < n_of_city; i++) {
		if (visited & (1 << i)) continue;
		if (weight[cur][i] == 0) continue;
		ret = min(ret, circular(i, visited | (1 << i)) + weight[cur][i]);
	}
	
	dist[cur][visited] = ret;

	return ret;
}
