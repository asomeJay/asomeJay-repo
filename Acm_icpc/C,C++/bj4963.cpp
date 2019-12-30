/* ¼¶ */

#include <iostream>
#include <stack>
#include<algorithm>

using namespace std;

int w, h, n_of_island;
int map[52][52];
bool is_visit[52][52];

void dfs(int x, int y) {
	int i, j, n_x, n_y;
	stack<pair<int, int>> s;

	s.push(make_pair(x,y));

	while (!s.empty()) {
		n_x = s.top().first;
		n_y = s.top().second;
		s.pop();

		is_visit[n_x][n_y] = 1;

		//left 
		if (is_visit[n_x - 1][n_y] == 0 && map[n_x - 1][n_y] == 1)
			s.push(make_pair(n_x - 1, n_y));

		// right
		if (is_visit[n_x+1][n_y] == 0 && map[n_x+1][n_y] == 1)
			s.push(make_pair(n_x + 1, n_y));

		// up
		if (is_visit[n_x][n_y-1] == 0 && map[n_x][n_y - 1] == 1)
			s.push(make_pair(n_x, n_y - 1));

		// down
		if (is_visit[n_x][n_y + 1] == 0 && map[n_x][n_y + 1] == 1)
			s.push(make_pair(n_x, n_y + 1));

		// diagonal up - left
		if (is_visit[n_x - 1][n_y - 1] == 0 && map[n_x-1][n_y - 1] == 1)
			s.push(make_pair(n_x - 1, n_y - 1));

		//diagonal down - left
		if (is_visit[n_x - 1 ][n_y + 1] == 0 && map[n_x - 1][n_y + 1] == 1)
			s.push(make_pair(n_x - 1, n_y + 1));

		// diagonal down - right
		if (is_visit[n_x + 1][n_y + 1] == 0 && map[n_x + 1][n_y + 1] == 1)
			s.push(make_pair(n_x + 1, n_y + 1));
		
		//diagonal up - right
		if (is_visit[n_x + 1][n_y - 1] == 0 && map[n_x + 1][n_y - 1] == 1)
			s.push(make_pair(n_x + 1, n_y - 1));
	}

}

int main(void) {
	int i, j, count;

	while (1) {
		scanf("%d %d", &w, &h);
		if (w == 0 && h == 0) break;

		count = 0;

		for (i = 1; i <= h; i++) {
			for (j = 1; j <= w; j++) 
				scanf("%d", &map[i][j]);
		}

		for (i = 1; i <= h; i++) {
			for (j = 1; j <= w; j++) {
				if (map[i][j] == 1 && is_visit[i][j] == 0) {
					dfs(i, j);
					count++;
				}
			}
		}

		printf("Land : %d\n", count);

		fill(&map[0][0], &map[51][52], 0);
		fill(&is_visit[0][0], &is_visit[51][52], 0);
	}



	return 0;
}