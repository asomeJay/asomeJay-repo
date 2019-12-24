/* 백트랙킹 기초 마지막 문제 */

#include <iostream>

using namespace std;

void dfs(int row);
int table[15];
int n, m;

int main(void) {
	int i, j, k;
	scanf("%d %d", &n, &m);

	for (i = 1; i <= n; i++) {
		table[1] = i;
		dfs(2);
	}

	return 0;
}

void dfs(int row) {
	int i, j, k;

	if (row > m) {
		for (i = 1; i < row; i++) {
			printf("%d ", table[i]);
		}
		printf("%\n");
		return;
	}

	for (i = 1; i <= n; i++) {
		if (i >= table[row - 1]) {
			table[row] = i;
			dfs(row + 1);
		}
	}
}