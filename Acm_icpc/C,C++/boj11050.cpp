/* 이항 계수 */

#include <iostream>

using namespace std;

int N, K;
int dp[20];

int main(void) {
	cin >> N >> K;

	dp[1] = dp[0] = 1;
	for (int i = 2; i <= 11; i++) {
		dp[i] = dp[i - 1] * i;
	}

	cout << dp[N] / (dp[N - K] * dp[K]);

	return 0;
}