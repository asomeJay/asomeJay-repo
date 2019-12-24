/* N과 M 백트랙킹 문제 기초*/

#include <iostream>

using namespace std;

void dfs(int);
int dp[10];
int n, m;
int main(void) {
	int i, j, k;
	scanf("%d %d", &n, &m);

	for (i = 1; i <= n; i++) {
		dp[1] = i;
		dfs(2);
	}


	return 0;
}

void dfs(int row) {
	int i, j, k;
	bool bool_tp[10] = { 0 };
	/*
	for (i = 1; i <= row - 1; i++) {
		bool_tp[dp[i]] = true;
	}*/

	if (row > m) {
		for (i = 1; i < row; i++)
			printf("%d ", dp[i]);

		printf("\n");
		return;
	}

	for (i = dp[row-1] + 1; i <= n; i++) {
		dp[row] = i;
		dfs(row + 1);
	}

}