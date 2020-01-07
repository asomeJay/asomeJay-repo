/* JUMP */

#include <iostream>
#include <queue>

using namespace std;

int s_of_table;
int table[102][102];
long long int dp[102][102];

int main(void) {
	int i, j, point;

	cin >> s_of_table;

	for (i = 1; i <= s_of_table; i++) {
		for (j = 1; j <= s_of_table; j++) {
			scanf("%d", &table[i][j]);
		}
	}

	dp[1][1] = 1;

	for (i = 1; i <= s_of_table; i++) {
		for (j = 1; j <= s_of_table; j++) {
			point = table[i][j];

			if (i != s_of_table && i + point <= s_of_table) {
				dp[i + point][j] += dp[i][j];
			}

			if (j != s_of_table && j + point <= s_of_table)
				dp[i][j + point] += dp[i][j];
		}
	}

	printf("%lld\n", dp[s_of_table][s_of_table]);
	/*
	for (i = 1; i <= s_of_table; i++) {
		for (j = 1; j <= s_of_table; j++) {
			printf("%lld ", dp[i][j]);
		}
		cout << '\n';
	}*/
	return 0;
}