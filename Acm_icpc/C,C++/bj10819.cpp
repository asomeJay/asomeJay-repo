/* 차이를 최대로 */

#include <iostream>
#include <algorithm>

using namespace std;

int num[9];
int is_visit[9];
int n_num, maxi, depth;

void dfs(int cur_depth, int, int);

int main(void) {
	int i, j, k;
	scanf("%d", &n_num);
	depth = n_num;
	maxi = 0;
	for (i = 1; i <= n_num; i++) 
		scanf("%d", &num[i]);
	
	for (i = 1; i <= n_num; i++) {
		is_visit[i] = 1;
		dfs(1, 0, i);
		is_visit[i] = 0;
	}
		

	printf("%d\n", maxi);
		
	return 0;
}

void dfs(int cur_depth, int cur_max, int cur_index) {

	if (cur_depth >= depth) {
		if (cur_max > maxi)
			maxi = cur_max;
		return;
	}

	int i;
	for (i = 1; i <= n_num; i++) {
		if (is_visit[i] == 0) {
			is_visit[i] = 1;
			dfs(cur_depth + 1, cur_max + (int)abs(num[cur_index] - num[i]), i);
			is_visit[i] = 0;
		}
	}
		
}