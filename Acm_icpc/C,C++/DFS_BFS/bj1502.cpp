/* 내리막길 */

#include <iostream>
#include <queue>

#define MAX_MAP 502
#define OUT_OF_RANGE 0

using namespace std;

int M, N, movable_road;
int map[MAX_MAP][MAX_MAP];
int dp[MAX_MAP][MAX_MAP];
bool is_dfs[MAX_MAP][MAX_MAP];

int dr[4] = { -1, 0,1,0 };
int dc[4] = { 0,1,0,-1 };

int dfs(int r, int c);
bool is_range(int r, int c);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int i, j, k;
	cin >> M >> N;

	for (i = 1; i <= M; i++) {
		for (j = 1; j <= N; j++) 
			cin >> map[i][j];
	}

	dfs(1, 1);

	cout << dp[1][1] << '\n';
	return 0;
}

int dfs(int r, int c) {
	if (is_range(r, c) == OUT_OF_RANGE) return 0;
	if (is_dfs[r][c] == 1) {
		return dp[r][c];
	}
	if (r == M && c == N) return 1;
	
	is_dfs[r][c] = 1;

	if (map[r][c] > map[r - 1][c]) {
		dp[r][c] += dfs(r - 1, c);
	}

	if (map[r][c] > map[r + 1][c]) {
		dp[r][c] += dfs(r + 1, c);
	}

	if (map[r][c] > map[r][c - 1]) {
		dp[r][c] += dfs(r, c - 1);
	}

	if (map[r][c] > map[r][c + 1]) {
		dp[r][c] += dfs(r, c + 1);
	}

	return dp[r][c];
}

bool is_range(int r, int c) {
	return r >= 1 && r <= M && c >= 1 && c <= N;
}