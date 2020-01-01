/* 보물상자 비밀번호 */

#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int T, N, K;
long long int seq[30];

void rotate();

int main(void) {
	int i, j, k, rotation, side, index, digit, size;
	long long int sum;

	scanf("%d", &T);

	set<long long int> hab;

	for (i = 1; i <= T; i++) {
		scanf("%d %d", &N, &K);
		size = sizeof(seq) / sizeof(seq[0]);

		fill(seq, seq + size, 0);
		
		getchar();

		for (j = 1; j <= N; j++) {
			seq[j] = getchar() - '0';

			if (seq[j] > 9) 
				seq[j] -= 7;
		}

		side = N / 4;

		for (rotation = 1; rotation <= side; rotation++) {
			for (j = 0; j < 4; j++) {

				sum = 0;
				digit = side - 1;
				for (k = 0; k < side; k++, digit--) {
					index = ((side * j) + k) + 1;

					sum += (seq[index] * (long long int)pow(16,digit));
//					printf("%d ", seq[index]);
				}
				/*
				printf("\n");
				printf("index : %d  j : %d  k : %d\n%lld\n", 
					index, j, k, sum);*/
				hab.insert(sum);
			}
			rotate();
		}

		set<long long int>::reverse_iterator it;
		/*
		for (it = hab.rbegin(), j = 0;
			j <= K - 1; it++, j++) {
			printf("#%d %lld\n", i, *it);
		}*/

		for (it = hab.rbegin(), j = 0; j < K - 1; it++, j++);
		printf("#%d %lld\n", i, *it);

		hab.clear();
	}

	return 0;
}

void rotate() {
	int i, temp;
	temp = seq[N];
//	printf("seq : %d %d\n", N, seq[N]);
	for (i = N-1; i >= 1; i--) 
		seq[i + 1] = seq[i];
	
	seq[1] = temp;
}