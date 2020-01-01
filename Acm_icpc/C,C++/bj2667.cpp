/* 단지번호 붙이기 DFS */

#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

int house[27][27];
bool is_visit[27][27];
int o[626];

int map, house_count, o_i;

void dfs(int x, int y) {
	int i, j, n_x, n_y, count;
	stack<pair<int, int>> s;
	s.push(make_pair(x,y));

	count = 0;
	is_visit[x][y] = 1;

	while (!s.empty()) {
		count++;

		n_x = s.top().first;
		n_y = s.top().second;

//		printf("count : %d n_x : %d  n_y : %d\n", count, n_x, n_y);


		s.pop();
		//up
		if (is_visit[n_x - 1][n_y] == 0 && house[n_x - 1][n_y] == 1) {
			s.push(make_pair(n_x - 1, n_y));
			is_visit[n_x -1][n_y] = 1;

		}

		//down
		if (is_visit[n_x + 1][n_y] == 0 && house[n_x + 1][n_y] == 1) {
			s.push(make_pair(n_x + 1, n_y));
			is_visit[n_x + 1][n_y] = 1;

		}

		//right
		if (is_visit[n_x][n_y + 1] == 0 && house[n_x][n_y + 1] == 1) {
			s.push(make_pair(n_x, n_y + 1));
			is_visit[n_x][n_y + 1] = 1;

		}

		//left
		if (is_visit[n_x][n_y - 1] == 0 && house[n_x][n_y - 1] == 1) {
			s.push(make_pair(n_x, n_y - 1));
			is_visit[n_x][n_y-1] = 1;

		}
	}
	o[o_i++] = count;
}

int main(void) {
	int i, j, k;

	scanf("%d", &map);

	getchar();

	for (i = 1; i <= map; i++) {
		for (j = 1; j <= map; j++) {
			house[i][j] = getchar() - '0';
//			printf("hos : %d ", house[i][j]);
		}
		getchar();
	}

	/*
	cout << '\n';

	for (int k = 1; k <= map; k++) {
		for (int m = 1; m <= map; m++) {
			printf("%d ", house[k][m]);
		}
		printf("\n");
	}*/

	for (i = 1; i <= map; i++) {
		for (j = 1; j <= map; j++) {
			if (is_visit[i][j] == 0 && house[i][j] == 1) {
				dfs(i, j);
				house_count++;
			}
		}
	}

	printf("%d\n", house_count);

	sort(o, o + o_i);
	for (i = 0; i < o_i; i++) {
		printf("%d ", o[i]);
	}


	return 0;
}