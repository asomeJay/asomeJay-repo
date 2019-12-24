/* 백트랙킹 : 스도쿠 */

#include <iostream>
#include <vector>

using namespace std;

bool row_check(int r, int num);
bool col_check(int c, int num);
bool square_check(int r, int c, int num);
void dfs(int idx);

int sdk[10][10];
bool sdk_row[10];
bool sdk_col[10];

int n;
vector<pair<int, int>> zero_xy;

int main(void) {
	int i, j;

	for (i = 1; i <= 9; i++) {
		for (j = 1; j <= 9; j++) {
			scanf("%d", &sdk[i][j]);
			if (sdk[i][j] == 0) {
				zero_xy.push_back({ i, j });
			}
		}
	}

	for (i = 1; i <= 9; i++) {
		int target_row = zero_xy[0].first;
		int target_col = zero_xy[0].second;

		if (row_check(target_row, i) && col_check(target_col, i) && square_check(target_row, target_col, i)) {
			sdk[target_row][target_col] = i;
			dfs(1);
			sdk[target_row][target_col] = 0;
		}
	}

	return 0;
}

bool row_check(int r, int num) {
	int i;

	for (i = 1; i <= 9; i++) {
		if (num == sdk[r][i]) {
			return false;
		}
	}
	return true;
}
 
bool col_check(int c, int num) {
	int i;

	for (i = 1; i <= 9; i++) {
		if (num == sdk[i][c]) {
			return false;
		}
	}

	return true;
} 

bool square_check(int r, int c, int num) {
	int i, j, can_x, can_y;
	
	can_x = (r - 1) / 3;
	can_x = can_x * 3 + 1;

	can_y = (c - 1) / 3;
	can_y = can_y * 3 + 1;

	for (i = can_x; i < can_x + 3; i++) {
		for (j = can_y; j < can_y; j++) {
			if (sdk[can_x][can_y] == num) {
				return false;
			}
		}
	}	
	return true;
}

void dfs(int idx) {
	int i, j;

	if (idx == zero_xy.size()) {
//		printf("\n\n");
		for (i = 1; i <= 9; i++) {
			for (j = 1; j <= 9; j++) {
				printf("%d ", sdk[i][j]);
			}
			printf("\n");
		}
		return;
	}

	for (i = 1; i <= 9; i++) {
		int target_row = zero_xy[idx].first;
		int target_col = zero_xy[idx].second;

		if (row_check(target_row, i) && col_check(target_col, i) && square_check(target_row, target_col, i)) {
			sdk[target_row][target_col] = i;
			dfs(idx + 1);
			sdk[target_row][target_col] = 0;
		}
	}
}