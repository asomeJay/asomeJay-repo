/* 색종이 붙이기 */

#include <iostream>
#include <algorithm>
#include <cmath>

#define MAX_MAP 11
#define CAN 1
#define CANT 0
#define MAX_PAPER 6
#define COVER 2
#define OUT_RANGE 0
#define FAIL -1

using namespace std;

int ans_paper;
int paper_map[MAX_MAP][MAX_MAP], rest[MAX_PAPER];

bool is_range(int r, int c);
void covering(int paper_num, int r, int c);
void recovering(int paper_num, int r, int c);
void recurse(int r, int c, int count_of_z, int );
bool chk_cover(int paper_num, int r, int c);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int i, j, one_count;
	ans_paper = 1000000;
	one_count = 0;

	for (i = 1; i <= 10; i++) {
		for (j = 1; j <= 10; j++) {
			cin >> paper_map[i][j];

			if (paper_map[i][j] == 1)
				one_count++;
		}
	}

	fill(rest, rest + MAX_PAPER, 5);

	recurse(1, 0, one_count, 0);
	if (ans_paper == 1000000) {
		cout << "-1";
		return 0;
	}

	cout << ans_paper;
	return 0;
}

bool is_range(int r, int c) {
	return r >= 1 && r <= 10 && c >= 1 && c <= 10;
}

void covering(int paper_num, int r, int c) {
	int i, j;

	rest[paper_num]--;
	for (i = r; i < r + paper_num; i++) {
		for (j = c; j < c + paper_num; j++) {
			paper_map[i][j] = COVER;
		}
	}
}

void recurse(int r, int c, int count_of_z, int count_of_p) {
	if (count_of_z == 0) {
		ans_paper = min(ans_paper, count_of_p);
		return;
	}

	int i, j, k;
	for (i = r-1; i <= 10; i++) {
		for (j = 1; j <= 10; j++) {
			if (paper_map[i][j] != 1)
				continue;

			for (k = 1; k <= 5; k++) {
				if (rest[k] == 0)
					continue;

				if (chk_cover(k, i, j) == CANT)
					return;

				covering(k, i, j);
				recurse(i, j, count_of_z - (int)pow(k, 2), count_of_p + 1);
				recovering(k, i, j);
			}
		}
	}
}

void recovering(int paper_num, int r, int c) {
	int i, j;
	rest[paper_num]++;
	for (i = r; i < r + paper_num; i++) {
		for (j = c; j < c + paper_num; j++) {
			paper_map[i][j] = 1;
		}
	}
}

bool chk_cover(int paper_num, int r, int c) {
	if (is_range(r + paper_num - 1, c + paper_num - 1) == OUT_RANGE)
		return CANT;

	int i, j;
	for (i = r; i < r + paper_num; i++) {
		for (j = c; j < c + paper_num; j++) {
			if (paper_map[i][j] != 1) {
				return CANT;
			}
		}
	}

	return CAN;
}