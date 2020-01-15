/* ÇÕºÐÇØ */
#include <iostream>

using namespace std;

int N, K, counti, k_fact;

long long int dp[201][201];

int main(void) {
	int i, j, k;
	scanf("%d %d", &N, &K);
	
	for (i = 0; i <= N; i++) {
		dp[0][i] = 0;
		dp[1][i] = 1;
	}
		
	for (i = 1; i <= K; i++) {
		dp[i][0] = 1;
	}

	for (i = 1; i <= K; i++) {
		for (j = 1; j <= N; j++) {
			for (k = 0; k <= j; k++) {
				dp[i][j] = dp[i][j] + dp[i - 1][j - k] % 1000000000;
			}
		}
	}
	/*
	for (i = 0; i <= K; i++) {
		for (j = 0; j <= N; j++) {
			printf("%lld ", dp[i][j]);
		}
		printf("\n");
	}*/


	printf("%lld\n", dp[K][N] % 1000000000);
	return 0;
}