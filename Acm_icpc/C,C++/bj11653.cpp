/* 소인수 분해 */

#include <iostream>

using namespace std;

int main(void) {
	int i, j, N;
	scanf("%d", &N);



	i = 2;

	while (N > 1) {
		if (i == N/2 + 1) {
			printf("%d\n", N);
			break;
		}
		for (i = 2; i <= N / 2; i++) {
			if (N % i == 0) {
				printf("%d\n", i);
				N /= i;
				break;
			}
		}
	}



	return 0;
}