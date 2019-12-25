/* 가장 긴 증가하는 수열 */

#include <iostream>

using namespace std;

int sequence[2000];
int count_seq[2000];

int main(void) {
	int n, i, j, k, min, max; scanf("%d", &n);

	for (i = 1; i <= n; i++) {
		scanf("%d", &sequence[i]);
		count_seq[i] = 1;
	}
		
	min = 0; 
	max = 1;

	for (i = 2; i <= n; i++) {
		min = 0;

		for (j = 1; j < i; j++) {
			if (sequence[i] > sequence[j]) {
				if (min < count_seq[j]) {
					min = count_seq[j];
				}
			}
		}
		count_seq[i] = min + 1;
		if (max < count_seq[i]) {
			max = count_seq[i];
		}
	}

	printf("%d\n", max);

	return 0;
}