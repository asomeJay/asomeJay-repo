/* 포도주 시식회 */
#include <iostream>
#include <algorithm>

using namespace std;

long long int dp[10001];
long long int grape[10001];

int main(void) {
	long long int maximum = 0;
	int i, j, k, n; cin >> n;
	cin >> grape[1] >> grape[2] >> grape[3];
	dp[1] = maximum = grape[1];
	dp[2] = grape[1] + grape[2];
	maximum = max(dp[1], dp[2]);
	dp[3] = max(grape[2] + grape[3], grape[1] + grape[3]);
	maximum = max(maximum, dp[3]);
	if (n == 1) return dp[1];
	if (n == 2) return dp[2];

	for (i = 4; i <= n; i++) {
		cin >> grape[i];
		dp[i] = max(dp[i - 3] + grape[i - 1] + grape[i], dp[i - 2] + grape[i]);
		if (maximum < dp[i]) maximum = dp[i];
	}
	cout << maximum << endl;

	return 0;
}