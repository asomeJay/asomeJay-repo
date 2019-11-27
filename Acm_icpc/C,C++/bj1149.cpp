/* DP Problem : RGB Street */

#include <iostream>
#include <algorithm>
#define LEN 1010
#define RGB 3
using namespace std;

int rgb_arr[LEN][RGB];

int main(void) {
	int i, j, k, n;
	int r, g, b;

	scanf("%d", &n);
	scanf("%d", &rgb_arr[0][0]); scanf("%d", &rgb_arr[0][1]); scanf("%d", &rgb_arr[0][2]);

	for (i = 1; i < n; i++) {
		scanf("%d", &r);
		rgb_arr[i][0] = min(rgb_arr[i - 1][1], rgb_arr[i - 1][2]) + r;

		scanf("%d", &g);
		rgb_arr[i][1] = min(rgb_arr[i - 1][0], rgb_arr[i - 1][2]) + g;
		// min3(a,b,c) == min(a, min(b,c))
		scanf("%d", &b);
		rgb_arr[i][2] = min(rgb_arr[i - 1][0], rgb_arr[i - 1][1]) + b;
	}

	printf("%d\n", min(rgb_arr[n - 1][0], min(rgb_arr[n - 1][1], rgb_arr[n - 1][2])));

	return 0;
}