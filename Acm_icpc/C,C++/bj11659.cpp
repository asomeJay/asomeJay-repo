/* 구간 합 구하기 4 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int table[100005], arr[100005];
vector<pair<int, int>> s_f;

int main(void) {
	int a, b, i, j, k, s,f, size, s_p, f_p, sum; scanf("%d %d", &a, &b);

	for (i = 1; i <= a; i++) {
		scanf("%d", &arr[i]);
		table[i] = table[i-1] + arr[i];
	}

	for (i = 0; i < b; i++) {

		scanf("%d %d", &s, &f);
		printf("%d\n", table[f] - table[s - 1]);
	}

	return 0;
}