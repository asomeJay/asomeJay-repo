/* 그림 교환 */

#include <iostream>
#include <algorithm>

#define MAX 16
using namespace std;

int dp[MAX][1 << MAX][10];
int artistery[MAX][MAX];
int artist, res;

int selling(int, int, int, int);

int main(void) {
	scanf("%d", &artist);
	getchar();

	for (int i = 0; i < artist; i++) {
		for (int j = 0; j < artist; j++) {
			artistery[i][j] = getchar() - '0';
		}
		getchar();
	}

	printf("%d", selling(0, 0, 1, 1));
	
	return 0;
}

int selling(int buyer, int cost, int n_people, int visit) {
	int& mini = dp[buyer][visit][cost];
	cout << mini << endl;
	if (mini != 0) return mini;

	mini = n_people;
	
	for (int next = 0; next < artist; next++) {
		if (visit & (1 << (next)) || (cost > artistery[buyer][next])) continue;
		mini = max(mini, selling(next, artistery[buyer][next], n_people + 1, visit | (1 << next)));
	}

	return mini;
}