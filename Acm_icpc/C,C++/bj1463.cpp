#include <iostream>
#include <algorithm>

using namespace std;

int dp[1000050];

int main(void) {
	int n, i, j, k; scanf("%d", &n);
	int min1, min2, min3;

	dp[0] = dp[1] = 0; dp[2] = dp[3] = 1;

	for (i = 4; i <= n; i++) {
		min1 = dp[i-1] + 1; min2 = 2000000; min3 = 2000000;

		if (i % 3 == 0) {
			min3 = dp[i / 3] + 1;
		}

		if (i % 2 == 0) {
			min2 = dp[i / 2] + 1;
		}

		dp[i] = min(min1, min(min2, min3));

	}
	printf("%d\n", dp[n]);

	return 0;
}