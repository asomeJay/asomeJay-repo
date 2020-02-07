/* 가장 큰 정사각형 */

#include <iostream>
#include <algorithm>

#define MAX_MAP 1001
#define IN_RANGE 1
#define OUT_OF_RANGE 0
#define CANT 0
#define CAN 1

using namespace std;

int map[MAX_MAP][MAX_MAP];
int dp_map[MAX_MAP][MAX_MAP];

int N, M;

bool can_make(int r, int c, int size);
bool is_range(int r, int c);

int main(void) {
	int i, j, k;

	cin >> N >> M;
	for (i = 1; i <= N; i++) {
		getchar();
		for (j = 1; j <= M; j++) {
			map[i][j] = getchar() - '0';
		}
	}

	int ans = 0, sizez = 1;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++) {
			if (map[i][j] == 0) continue;

			while (can_make(i, j, sizez) == CAN) {
				ans = max(ans, sizez);
				sizez++;
			}
		}
	}

	cout << ans * ans<< '\n';
	return 0;
}

bool is_range(int r, int c) {
	return r <= N && 1 <= r && 1 <= c && c <= M;
}

bool can_make(int r, int c, int size) {
	if (is_range(r + size - 1, c + size - 1) == CANT)
		return CANT;

	int i, j;
	for (i = r; i < r + size; i++) {
		for (j = c; j < c + size; j++) {
			if (map[i][j] != 1)
				return CANT;
		}
	}

	return CAN;

}