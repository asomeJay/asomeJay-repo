#include <iostream>

using namespace std;

long long int dp[1001];

int main(void) {
	int i, j, k, n; cin >> n;

	dp[0] = 0; dp[1] = 1; dp[2] = 3;
	for (i = 3; i <= n; i++) {
		dp[i] = (dp[i - 1] + (2 * dp[i - 2]) % 10007) % 10007;
	}
	
	cout << dp[n] << endl;
	return 0;
}