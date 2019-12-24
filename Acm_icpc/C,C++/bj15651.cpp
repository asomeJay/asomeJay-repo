/* N과 M 백트랙킹 */

#include <iostream>

using namespace std;

void dfs(int row);

int table[10];
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
		printf("\n");
		return;
	}

	for (i = 1; i <= n; i++) {
		table[row] = i;
		dfs(row + 1);
	}

}