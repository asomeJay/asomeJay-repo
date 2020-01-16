/* 백트랙킹 기본 */

#include <iostream>

using namespace std;

int table[10];

int n, m;
void dfs(int);

int main(void) {
	int i, j, k; cin >> n >> m;

	for (i = 1; i <= n; i++) {
		table[1] = i;
		dfs(2);
	}

	return 0;
}

void dfs(int row) {
	int i, j, k;
	bool bool_tb[10] = { 0 };
	for (i = 1; i <= row-1; i++) {
		bool_tb[table[i]] = true;
	}

	if (row > m) {
		for (i = 1; i <= m; i++) {
			printf("%d ", table[i]);
		}
		cout << '\n';
		return;
	}

	for (i = 1; i <= n; i++) {
		if (bool_tb[i] == true) continue;
		table[row] = i;

		dfs(row + 1);
	}
}