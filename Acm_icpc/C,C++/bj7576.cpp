/* ≈‰∏∂≈‰ */

#include <iostream>
#include <algorithm>
#include <stack>

#define UNRIPE 0
#define EMPTY -1 
#define RIPE 1
#define UNVISIT 0 
#define VISIT 0

using namespace std;

int r, c, day, zero;

int box[1002][1002];
bool is_visit[1002][1002];

void initi(stack<pair<int,int>> &s, stack<pair<int,int>> &t);
void riped();

int main(void) {
	int i, j, k;
	stack<pair<int,int>> even;
	stack < pair<int, int>> odd;
	fill(&box[0][0],& box[1001][1002], EMPTY);

	scanf("%d %d", &c, &r);

	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			scanf("%d", &box[i][j]);
			if (box[i][j] == 1) {
				odd.push(make_pair(i, j));
				is_visit[i][j] = 1;
			}
				
			else if (box[i][j] == 0)
				zero++;
		}
	}

	while (!even.empty() || !odd.empty()) {

		if (!odd.empty()) {
			initi(odd, even);
			day++;
		}

		if (!even.empty()) {
			initi(even, odd);
			day++ ;
		}
	}

	if (zero != 0)
		printf("-1\n");
	else 
		printf("%d\n", day - 1);

	return 0;
}

void initi(stack<pair<int,int>> &s, stack<pair<int, int>>& t) {
	int n_x, n_y;
	while (!s.empty()) {
		n_x = s.top().first;
		n_y = s.top().second;

		s.pop();
		//up
		if (is_visit[n_x - 1][n_y] == UNVISIT
			&& box[n_x - 1][n_y] == UNRIPE) {
			is_visit[n_x - 1][n_y] = VISIT;
			box[n_x - 1][n_y] = RIPE;
			t.push(make_pair(n_x - 1, n_y));
			zero--;
		}

		//down
		if (is_visit[n_x + 1][n_y] == UNVISIT
			&& box[n_x + 1][n_y] == UNRIPE) {
			is_visit[n_x + 1][n_y] = VISIT;
			box[n_x + 1][n_y] = RIPE;
			t.push(make_pair(n_x + 1, n_y));
			zero--;
		}

		//left
		if (is_visit[n_x][n_y - 1] == UNVISIT 
			&& box[n_x][n_y - 1] == UNRIPE) {
			is_visit[n_x][n_y - 1] = VISIT;
			box[n_x][n_y - 1] = RIPE;
			t.push(make_pair(n_x, n_y - 1));
			zero--;
		}

		//right
		if (is_visit[n_x][n_y + 1] == UNVISIT 
			&& box[n_x][n_y + 1] == UNRIPE) {
			is_visit[n_x][n_y + 1] = VISIT;
			box[n_x][n_y + 1] = RIPE;
			t.push(make_pair(n_x, n_y + 1));
			zero--;
		}
	}
}