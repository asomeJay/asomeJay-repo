/* 차이를 최대로 */

#include <iostream>
#include <algorithm>

using namespace std;

int num[9];
int n_num, maxi;

void dfs(int cur_depth, int);

int main(void) {
	int i, j, k;
	scanf("%d", &n_num);

	for (i = 1; i <= n_num; i++) 
		scanf("%d", &num[i]);

	sort(num, num + n_num);
	k = 0;
	if (n_num % 2 == 1) {// 홀수
		for (i = 1; i <= n_num / 2; i++) {
			k += abs(num[i] - num[n_num - i]);
			k += abs(num[i + 1] - num[n_num - i]);
		}
	}

	else {
		for (i = 1; i <= n_num / 2; i++) {
			k += abs(num[i] - num[n_num - i + 1]);
			k += abs(num[i + 1] - num[n_num - i + 1]);
		}
	}

	printf("%d\n", k);
		

	return 0;
}