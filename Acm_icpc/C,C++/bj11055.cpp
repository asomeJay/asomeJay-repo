/* 가장 큰 증가하는 부분 수열(합) */

#include <iostream>

using namespace std;

int seq[1001], sum_seq[1001];
int s_seq;

int main(void) {
	int i, j, k, sum, max, ans_max;

	scanf("%d", &s_seq);
	for (i = 1; i <= s_seq; i++)
		scanf("%d", &seq[i]);

	sum_seq[1] = seq[1]; ans_max = seq[1];
	for (i = 2; i <= s_seq; i++) {
		max = 0;
		for (j = 1; j < i; j++) {
			if (seq[i] > seq[j]) {
				if (max < sum_seq[j])
					max = sum_seq[j];
			}
		}
		sum_seq[i] = max + seq[i];

		if (sum_seq[i] > ans_max)
			ans_max = sum_seq[i];
	}

	printf("%d\n", ans_max);

	return 0;
}