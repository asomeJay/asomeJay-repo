/* 최소비용 구하기 */

#include <iostream>
#include <climits>

#define MAX_CITY 1001
#define MAXMAX 100001

using namespace std;

int n_of_city, n_of_bus, mini, start_pos, target_pos;
int city[MAX_CITY][MAX_CITY];
int dist[MAX_CITY];
int found[MAX_CITY];

int choose();
void shortest_path();

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int i, j, k, s_c, a_c, weight;
	cin >> n_of_city >> n_of_bus;

	for (i = 1; i <= n_of_city; i++) {
		for (j = 1; j <= n_of_city; j++) {
			city[i][j] = MAXMAX;
		}
	}

	for (i = 1; i <= n_of_bus; i++) {
		cin >> s_c >> a_c >> weight;
		city[s_c][a_c] = weight;
	}

	cin >> start_pos >> target_pos;
	shortest_path();
	cout << dist[target_pos] << '\n';
	return 0;
}

int choose() {
	int mini = INT_MAX;
	int minpos;
	int i, j;
	for (i = 1; i <= n_of_city; i++) {
		if (dist[i] < mini && !found[i]) {
			mini = dist[i];
			minpos = i;
		}
	}
	return minpos;

}

void shortest_path() {
	int i, j, u;

	dist[start_pos] = 0;
	for (i = 1; i <= n_of_city; i++) {
		dist[i] = city[start_pos][i];
	}

	found[start_pos] = 1;
	for (i = 1; i <= n_of_city - 1; i++) {
		u = choose();
		found[u] = true;

		for (j = 1; j <= n_of_city; j++) {
			if (found[j] != 1) {
				if (dist[u] + city[u][j] < dist[j])
					dist[j] = dist[u] + city[u][j];
			}
		}
	}
}