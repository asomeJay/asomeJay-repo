#include <iostream>
#include <algorithm>

#define TABLE 310
using namespace std;

int dp[TABLE];
int arr[TABLE];

int main(void) {
	int n, i, j, maxi = 0; scanf("%d", &n);

	for (i = 0; i < n; i++) {
		scanf("%d", &dp[i]);
	}

	arr[0] = dp[0];
	arr[1] = dp[0] + dp[1];

	for (i = 2; i < n; i++) {
		arr[i] = max(dp[i] + arr[i - 2], dp[i] + dp[i - 1] + arr[i - 3]);
	}

	printf("%d\n", arr[n-1]);
	return 0;
}