/* Easy Stairway Number */
#include <iostream>

using namespace std;

long long int dp[101][11];
long long solution(int n);
int main(void) {
	int i, j, k, n; cin >> n;
	long long int result = 0;
	dp[1][0] = 0;
	for (i = 1; i <= 9; i++) {
		dp[1][i] = 1;
	}

	for (i = 2; i <= n; i++) {
		for (j = 0; j <= 9; j++) {
			if (j == 0)dp[i][0] = dp[i - 1][1] % 1000000000;
			else if (j == 9) dp[i][9] = dp[i - 1][8] % 1000000000;
			else {
				dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1] % 1000000000;
			}
 		}
	}

	for (i = 0; i <= 9; i++) {
		result += dp[n][i];
		result %= 1000000000;
	}
	cout << solution(n) << endl;
	printf("%lld\n", result);

	return 0;
}

long long solution(int n) {

	long long ret = 0;
	const long long mod = 1000000000;

	long long dp[101][10];
	dp[1][0] = 0;

	for (int i = 1; i <= 9; i++) {
		dp[1][i] = 1;
	}

	if (n == 1)
		return 9;

	for (int j = 2; j <= n; j++) {

		for (int k = 0; k <= 9; k++) {
			if (k == 0) dp[j][k] = dp[j - 1][1] % mod;
			else if (k == 1) dp[j][k] = (dp[j - 1][2] + dp[j - 1][0]) % mod;
			else if (k == 9) {
				dp[j][k] = (dp[j - 1][8]) % mod;
			}
			else {
				dp[j][k] = (dp[j - 1][k - 1] + dp[j - 1][k + 1]) % mod;
			}
		}
	}

	for (int i = 0; i < 10; i++) {
		//문제가 되는 부분
		// i = 1부터 시작해야 되지 않는지?
		ret = (ret + dp[n][i]) % mod;
	}

	return ret % mod;
}