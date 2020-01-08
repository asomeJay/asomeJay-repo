/* ¼û¹Ù²ÀÁú */

#include <iostream>
#include <stack>
#include <algorithm>

#define MAX 200001

using namespace std;

int N, K;
int T[MAX];

int main(void) {
	scanf("%d %d", &N, &K);
	int i, j, k;

	fill(T, T + MAX, 200000);

	T[N] = 0; 
	//T[N + 1] = 1;

	for (i = N-1; i > 0; i--) 
		T[i] = T[i + 1] + 1;
	
	for (i = 0; i <= 100000; i++) {

		if(i != 0)
			T[i - 1] = (T[i - 1] > T[i] + 1 ? T[i] + 1 : T[i - 1]);
		
		
		T[2 * i] = (T[2 * i] > T[i] + 1 ? T[i] + 1 : T[2 * i]);
		T[i + 1] = (T[i + 1] > T[i] + 1 ? T[i] + 1 : T[i + 1]);
	}

	for (i = 100000; i >= N; i--) {
		if (T[i - 1] > T[i] + 1) {
			T[i - 1] = T[i] + 1;
		}
	}

	/*
	for (i = 1; i <= K; i++) 
		printf("T[%d] : %d\n", i, T[i]);
	*/
	printf("%d\n", T[K]);

	return 0;
}