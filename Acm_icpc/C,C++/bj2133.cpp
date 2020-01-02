/* 타일 채우기 */

#include <iostream>

using namespace std;

int dp[31];

int main(void) {
	int n, i,j;
	scanf("%d", &n);

	dp[0] = 1; dp[1] = dp[3] = 0; dp[2] = 3; dp[4] = 11;
	for (i = 5; i <= n; i++) {
		if (i % 2 == 1) 
			dp[i] = 0;
		else
			dp[i] = dp[i - 2] * 3 + dp[i - 4] * 2 + 2;
	}

	printf("%d\n", dp[n]);

	return 0;
}