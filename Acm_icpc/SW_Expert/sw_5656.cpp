/* 모의 SW 역량 테스트 벽돌 깨기*/

#include <iostream>
#include <algorithm>
#include <stack>

#define highe 20
#define BRICK 20

using namespace std;

int brick_break(int, int, int [BRICK][BRICK], int [highe], int);
void shooting(int, int, int, int [BRICK][BRICK], int [highe], int);

int depth_limit, smallest_brick;
int r, c;

int main(void)
{
	int test_case, i, j, k, left_brick;
	
	int T;
	int brick_table[BRICK][BRICK];
	int highest_point[highe];

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		smallest_brick = 21000000;

		fill(&brick_table[0][0], &brick_table[BRICK-1][BRICK], 0);
		fill(&highest_point[0], &highest_point[highe], 0);

		scanf("%d %d %d", &depth_limit, &c, &r);
		left_brick = 0;

		for (i = 1; i <= r; i++) {
			for (j = 1; j <= c; j++) {
				scanf("%d", &brick_table[i][j]);
				if (brick_table[i][j] != 0) {
					if (highest_point[j] == 0) {
						highest_point[j] = i;
					}
					left_brick++;
				}
			}
		}

		for (i = 1; i <= c; i++) {
			shooting(1, left_brick, i, brick_table, highest_point, i);
		}
			
		printf("#%d %d\n", test_case, smallest_brick);
	}
	return 0;
}

void shooting(int cur_depth, int n_left_brick, int pos, int table_[BRICK][BRICK], int high[highe], int index) {
	int ii, jj;
	if (cur_depth > depth_limit) {
		if (n_left_brick < smallest_brick) {
			smallest_brick = n_left_brick;
		}

		return;
	}

	int i, j, left_brick;
	int table[BRICK][BRICK], highest_point[highe];

	copy(&table_[0][0], &table_[0][0] + BRICK * BRICK, &table[0][0]);
	copy(high, high + highe, highest_point);

	left_brick = brick_break(pos, n_left_brick, table, highest_point, 1);

	for (i = 1; i <= c; i++) {
		shooting(cur_depth + 1, left_brick, i, table, highest_point, i);
	}
}

/* 벽돌을 깨는 함수(), 해당 position(y값)의 highest point가 있으니까, 그 두개 연합해서 정확한 좌표값 알아내고, table을 매개변수로 받기 때문에 거기를 기준으로 벽돌 다 때려뿌숨
*/

int brick_break(int position, int n_left_brick, int t[BRICK][BRICK], int p[highe], int index) {
	if (t[p[position]][position] == 0) return n_left_brick;

	int i, j, k,n_r, n_c, bound, n_brick, ccc;

	stack<pair<int, int>> axis;
	stack<int> range;
	n_r = p[position]; n_c = position;

	axis.push(make_pair(n_r, n_c));
	range.push(t[n_r][n_c]);

	n_brick = n_left_brick - 1;
	t[n_r][n_c] = 0;
	
	while (!axis.empty() || !range.empty()) {
		n_r = axis.top().first;
		n_c = axis.top().second;
		bound = range.top();
		axis.pop(); range.pop();

		//up : 벽돌 옮기기 + 최고점 갱신
		for (k = 1; k < bound; k++) {
			// up 
			if (n_r - k > 0 && t[n_r - k][n_c] != 0) {
				axis.push(make_pair(n_r - k, n_c));
				range.push(t[n_r - k][n_c]);
				t[n_r - k][n_c] = 0;
				
				n_brick--;
			}

			// down
			if (n_r + k <= r && t[n_r + k][n_c] != 0) {
				axis.push(make_pair(n_r + k, n_c));
				range.push(t[n_r + k][n_c]);
				t[n_r + k][n_c] = 0;

				n_brick--;
			}

			// left
			if (n_c - k > 0 && t[n_r][n_c - k] != 0) {
				axis.push(make_pair(n_r, n_c - k));
				range.push(t[n_r][n_c - k]);
				t[n_r][n_c - k] = 0;
				
				n_brick--;
			}

			// right
			if (n_c + k <= c && t[n_r][n_c + k] != 0) {
				axis.push(make_pair(n_r, n_c + k));
				range.push(t[n_r][n_c + k]);
				t[n_r][n_c + k] = 0;
				
				n_brick--;
			}
		}
	}

	// 벽돌 옮기기 시작
	int n_zero;

	for (i = 1; i <= c; i++) {
		n_zero = r;
		for (j = r; j > 0; j--) {
			if (t[j][i] != 0) {
				p[i] = n_zero;
				t[n_zero--][i] = t[j][i];

			}
		}
		for (j = n_zero; j > 0; j--) {
			t[j][i] = 0;
		}
	}
	return n_brick;
}