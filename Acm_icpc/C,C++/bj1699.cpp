/* bj1699 : Á¦°ö¼öÀÇ ÇÕ */

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int dp[1005001];
int temp[400];

int main(void) {
	int n, i, j; scanf("%d", &n);
	int count = 0, candi1, candi2;
	dp[0] = 1; dp[1] = 1;
	for (i = 1; i <= (int)sqrt(n); i++) {
		temp[i] = pow(i, 2);
		dp[temp[i]] = 1;
		if (pow(i, 2) == n) {
			printf("1\n");
			return 0;
		}
	}

	for (i = 2; i <= n; i++) {
		if (dp[i]) continue;
		dp[i] = 5000;
		for (j = 0; i - temp[j] > 0; j++) {
			dp[i] = min(dp[i], dp[i - temp[j]] + 1);
		}
	}

	printf("%d\n", dp[n]);
	return 0;
}