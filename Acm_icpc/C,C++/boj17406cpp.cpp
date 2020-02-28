/* 배열 돌리기 4 */

#include <iostream>
#include <algorithm>

#define MAX_MAP 51

using namespace std;

int N, M, K, RESULT = 2100000000;
int rotate_info[7][4];
bool is_used[7];

void rotated(int r, int c, int s, int map[MAX_MAP][MAX_MAP]);
void depth(int d, int[MAX_MAP][MAX_MAP]);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	int i, j, k;
	int map[MAX_MAP][MAX_MAP];

	cin >> N >> M >> K;

	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}

	for (i = 1; i <= K; i++) 
		cin >> rotate_info[i][0] >> rotate_info[i][1] >> rotate_info[i][2];

	depth(0, map);
	cout << RESULT;

	return 0;
}

int sum(int map[MAX_MAP][MAX_MAP]) {
	int i, j, t_sum, ans;
	ans = 2100000000;

	for (i = 1; i <= N; i++) {
		t_sum = 0;
		for (j = 1; j <= M; j++) {
			t_sum += map[i][j];
		}
		ans = min(ans, t_sum);
	}

	return ans;
}

void rotated(int r, int c, int s, int map[MAX_MAP][MAX_MAP]) {
	while(s) {
		int i;
		int rs = r - s, cs = c - s;
		int re = r + s, ce = c + s;
		s--;

		int t = map[rs][ce];
		for (i = ce; i > cs; i--)
			map[rs][i] = map[rs][i - 1];

		for (i = rs; i < re; i++)
			map[i][cs] = map[i + 1][cs];

		for (i = cs; i < ce; i++)
			map[re][i] = map[re][i + 1];

		for (i = re; i > rs; i--)
			map[i][ce] = map[i - 1][ce];

		map[rs + 1][ce] = t;
	}
}

void depth(int d, int t_map[MAX_MAP][MAX_MAP]) {
	if (d >= K) {
		RESULT = min(RESULT, sum(t_map));
		return;
	}

	int i, j;
	int copy_map[MAX_MAP][MAX_MAP];
	copy(&t_map[0][0], &t_map[MAX_MAP - 1][MAX_MAP], &copy_map[0][0]);
	
	for (i = 1; i <= K; i++) {
		if (is_used[i] == false) {
			is_used[i] = true;

			rotated(rotate_info[i][0], rotate_info[i][1], rotate_info[i][2], copy_map);

			depth(d + 1, copy_map);
			copy(&t_map[0][0], &t_map[MAX_MAP - 1][MAX_MAP], &copy_map[0][0]);
			is_used[i] = false;
		}
	}
}