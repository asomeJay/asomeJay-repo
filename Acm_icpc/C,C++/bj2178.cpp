/* ¹Ì·Î Å½»ö */

#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

int row, col, ans_count;
int map[102][102];
int is_visit[102][102];

void dfs(int x, int y) {
	int i, j, n_x, n_y, count, flag;
	count = 0; flag = 0;

	queue<pair<int, int>> s;
	s.push(make_pair(x, y));
	is_visit[x][y] = 5;
	while (!s.empty()) {
		flag = 0; count++;
		n_x = s.front().first;
		n_y = s.front().second;
		s.pop();

		//is_visit[n_x][n_y] = 5;

		//up 
		if (is_visit[n_x - 1][n_y] == 0 && map[n_x - 1][n_y] == 1) {
			s.push(make_pair(n_x - 1, n_y));
			is_visit[n_x - 1][n_y] = 3;
		}

		// down
		if (is_visit[n_x + 1][n_y] == 0 && map[n_x + 1][n_y] == 1) {
			s.push(make_pair(n_x + 1, n_y));
			is_visit[n_x + 1][n_y] = 1;

		}
			
		// left
		if (is_visit[n_x][n_y - 1] == 0 && map[n_x][n_y - 1] == 1) {
			s.push(make_pair(n_x, n_y - 1));
			is_visit[n_x][n_y - 1] = 2;

		}
			
		// right
		if (is_visit[n_x][n_y + 1] == 0 && map[n_x][n_y + 1] == 1) {
			s.push(make_pair(n_x, n_y + 1));
			is_visit[n_x][n_y + 1] = 4;

		}
			
		//if (flag == 0) 
		//	count--;
	}
}

void direct() {
	int x, y;
	x = row; y = col; ans_count = 0;
	while (x != 1 || y != 1) {
		ans_count++;
		if (is_visit[x][y] == 1) {
			x--;
		}
		else if (is_visit[x][y] == 2) {
			y++;
		}
		else if (is_visit[x][y] == 3) {
			x++;
		}
		else if (is_visit[x][y] == 4) {
			y--;
		}
	}
}

int main(void) {
	scanf("%d %d", &row, &col);
	 
	getchar();

	int i, j, k;
	ans_count = INT_MAX;
	for (i = 1; i <= row; i++) {
		for (j = 1; j <= col; j++)
			map[i][j] = getchar() - '0';
		getchar();
	}

	dfs(1, 1);

	direct();
	printf("%d\n", ans_count + 1);

	return 0;
}