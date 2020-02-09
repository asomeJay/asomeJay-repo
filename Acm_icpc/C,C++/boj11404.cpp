/* 플로이드 */

#include <iostream>
#include <algorithm>

#define INFA 2100000
#define MAX_MAP 105
using namespace std;

int N_OF_CITY, N_OF_BUS;
int map[MAX_MAP][MAX_MAP];

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int i, j, k, s ,a, w;

	cin >> N_OF_CITY >> N_OF_BUS;

	for (i = 1; i <= N_OF_CITY; i++) {
		for (j = 1; j <= N_OF_CITY; j++) {
			if (i == j) {
				map[i][j] = 0;
			}
			else {
				map[i][j] = INFA;
			}
		}
	}

	for (i = 1; i <= N_OF_BUS; i++) {
		cin >> s >> a >> w;
		map[s][a] = min(map[s][a], w);
	}
	 
	for (i = 1; i <= N_OF_CITY; i++) {
		for (j = 1; j <= N_OF_CITY; j++) {
			for (k = 1; k <= N_OF_CITY; k++) {
				map[k][j] = min(map[k][j], map[k][i] + map[i][j]);
			}
		}
	}
	
	for (i = 1; i <= N_OF_CITY; i++) {
		for (j = 1; j <= N_OF_CITY; j++) {
			if (map[i][j] == INFA)
				map[i][j] = 0;
			cout << map[i][j] << " ";
		}
		cout << '\n';
	}

	return 0;
}