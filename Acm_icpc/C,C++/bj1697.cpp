/* ¼û¹Ù²ÀÁú */

#include <iostream>
#include <queue>
#include <algorithm>

#define MAX 100001

using namespace std;

int N, K;
int T[MAX];

int main(void) {
	scanf("%d %d", &N, &K);
	int i, j, k;
	queue<int> s;

	s.push(N);
	while (!s.empty()) {
		k = s.front();
		j = T[k];
		s.pop();
		if (k == K) break;
		if (k - 1 >= 0 && (T[k - 1] == 0 || T[k - 1] > j + 1)) {
			T[k - 1] = j + 1;
			s.push(k - 1);
		}

		if (2 * k < MAX && (T[2 * k] == 0 || T[2 * k] > j + 1)) {
			T[2 * k] = j + 1;
			s.push(2 * k);
		}

		if (k + 1 < MAX && k + 1 <= K&& (T[k + 1] == 0 || T[k + 1] > j + 1)) {
			T[k + 1] = j + 1;
			s.push(k + 1);
		}
	}

	T[N] = 0;
	/*
	fill(T, T + MAX, 200000);

	T[N] = 0; 

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
	*/
	printf("%d\n", T[K]);

	return 0;
}