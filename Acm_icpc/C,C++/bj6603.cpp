/* 백트랙킹 문제 : 로또 */

#include <iostream>
#include <algorithm>

using namespace std;

int set_lotto[50];
int ans[50]; 
bool is_used[50];

void lotto(int k, int limit, int);

int main(void) {
	int n, i, j, k, temp;

	while (1) {
		cin >> k;
		//fill(set_lotto, set_lotto + k, 0);
		if (k == 0) return 0;

		for (i = 1; i <= k; i++) 
			scanf("%d", &set_lotto[i]);
		
		for (i = 1; i <= k; i++) {
			is_used[i] = 1;

			ans[1] = set_lotto[i];
			lotto(2, k, i);

			is_used[i] = 0;
		}

		printf("\n");
	}
	
	return 0;
}

void lotto(int k, int limit, int index) {
	int i, j;

	if (k > 6) {
//		printf("k : %d   limit : %d  \n", k, limit);
		for (i = 1; i <= 6; i++) {
//			if (ans[i] != 0) {
				printf("%d ", ans[i]);
			}
//		}
		printf("\n");
		return;
	}

	for (i = index + 1; i <= limit; i++) {
		j = set_lotto[i];

		if (is_used[i] == 0) {
			is_used[i] = 1;
			ans[k] = j;
			lotto(k + 1, limit, i);
			is_used[i] = 0;
		}
	}
}