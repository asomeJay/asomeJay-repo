/* 가장 긴 감소하는 부분 수열 */

#include <iostream>

using namespace std;

int seq[1001];
int n_seq[1001];

int main(void) {
	int i, max, ans, n, t; scanf("%d", &n);

	for (i = 1; i <= n; i++) {
		scanf("%d", &seq[i]);
		n_seq[i] = 1;
	}

	ans = 1;
	for (i = 2; i <= n; i++) {
		max = 0;
		for (int j = 1; j <= i - 1; j++) {
			if (seq[i] < seq[j]) {
				if (max < n_seq[j]) {
					max = n_seq[j];
				}
			}
		}
		n_seq[i] = max + 1;
		if (ans < n_seq[i]) ans = n_seq[i];
	}

	printf("%d\n", ans);
	return 0;
}