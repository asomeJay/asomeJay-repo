/* °æ»ç·Î */

#include <iostream>
#define MAX_MAP 100 + 1
#define CAN 1
#define CANT 0

using namespace std;

bool row_runway(int row);
bool col_runway(int col);
bool is_range(int r, int c);

int N, L, can_runway;
int map[MAX_MAP][MAX_MAP];

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> L;
	int i, j, k;

	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}

	for (i = 1; i <= N; i++) {
		if (row_runway(i) == CAN)
			can_runway++;
		if (col_runway(i) == CAN)
			can_runway++;
	}

	cout << can_runway;

	return 0;
}

bool row_runway(int row) {
	int i, j;
	bool is_install[MAX_MAP] = { 0 };

	for (i = 2; i <= N; i++) {
		if (abs(map[row][i] - map[row][i - 1]) >= 2)
			return CANT;
		if (map[row][i] > map[row][i - 1]) {
			if (is_range(i - 1, i - L) == CANT)
				return CANT;
			for (j = i - 1; j > i - L; j--) {
				if ((map[row][j] != map[row][j - 1] || is_install[j] == 1))
					return CANT;
				is_install[j] = true;
			}
			if (is_install[i - L] == 1)
				return CANT;
			is_install[i - L] = 1;
		}

		if (map[row][i] < map[row][i - 1]) {
			if (is_range(i, i + L - 1) == CANT)
				return CANT;
			for (j = 0; j < L - 1; j++) {
				if ((map[row][i + j] != map[row][i + j + 1]) || (is_install[i + j] == 1))
					return CANT;
				is_install[i + j] = true;
			}
			if (is_install[i + L-1] == 1)
				return CANT;
			is_install[i + L-1] = 1;
		}

	}
	return CAN;
}

bool col_runway(int col) {
	int i, j;
	bool is_install[MAX_MAP] = { 0 };

	for (i = 2; i <= N; i++) {
		if (abs(map[i][col] - map[i-1][col]) >= 2)
			return CANT;
		if (map[i][col] > map[i-1][col]) {
			if (is_range(i - 1, i - L) == CANT)
				return CANT;
			for (j = i - 1; j > i - L; j--) {
				if ((map[j][col] != map[j-1][col] || is_install[j] == 1))
					return CANT;
				is_install[j] = true;
			}
			if (is_install[i - L] == 1)
				return CANT;
			is_install[i - L] = 1;
		}

		if (map[i][col] < map[i-1][col]) {
			if (is_range(i, i + L - 1) == CANT)
				return CANT;
			for (j = 0; j < L - 1 ; j++) {
				if ((map[i+j][col] != map[i+j+1][col]) || (is_install[i + j] == 1))
					return CANT;
				is_install[i + j] = true;
			}
			if (is_install[i + L - 1] == 1)
				return CANT;
			is_install[i + L - 1] = 1;
		}
	}
	return CAN;
}

bool is_range(int r, int c) {
	return r >= 1 && r <= N && c >= 1 && c <= N;
}