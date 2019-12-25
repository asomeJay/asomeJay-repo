/* 랜선 자르기 */

#include <iostream>
#include <vector>

using namespace std;

long long int dp[10001];

int main(void) {
	long long int N, K, i, j, k, left, right, middle, line_cnt, ans, ans_middle;
	left = 0;  right = 0; ans = 999999999;

	scanf("%lld %lld", &K, &N);

	for (i = 1; i <= K; i++) {
		scanf("%lld", &dp[i]);

		if (dp[i] > right) 
			right = dp[i];
	}

	ans_middle = 0;
	while (left <= right) {
		line_cnt = 0;
		middle = (left + right) / 2;

		if (middle == 0) {
			left++;
			continue;
		}

		for (i = 1; i <= K; i++) {
			line_cnt += dp[i] / middle;
		}

		if (line_cnt >= N) {
			if (ans >= line_cnt) {
				ans = line_cnt;
				if(ans_middle < middle)
					ans_middle = middle;
			}
			left = middle + 1;
		}
		else {
			right = middle - 1;
		}
	}

	printf("%lld\n", ans_middle);
	return 0;
}