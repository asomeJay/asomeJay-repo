/* 홈 방범 서비스 */

// 1. 손해만 안보면 된다.
// 2. 최대한 많은 집에 서비스를 제공하라

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX_CITY 20 + 1
#define IN_RANGE 1

using namespace std;

bool city[MAX_CITY][MAX_CITY];
int n_of_city, price_per_home;

bool is_range(int r, int c);
void init();
int operating_cost(int depth, int r, int c);
int securitied_house(int depth, int r, int c);

int main(void) {
	int tcase, ans;
	cin >> tcase;
	for (int i = 0; i < tcase; i++) {
		init();
		cin >> n_of_city >> price_per_home;

		for (int j = 1; j <= n_of_city; j++) {
			for (int k = 1; k <= n_of_city; k++) {
				cin >> city[j][k];
			}
		}

		ans = 0;
		for (int j = 1; j <= n_of_city; j++) {
			for (int k = 1; k <= n_of_city; k++) {

				int depth = 1;
				while (depth++ <= 20) {
					int op_cost = operating_cost(depth, j, k);
					int sec_home = securitied_house(depth, j, k);

					if (op_cost <= (sec_home * price_per_home))
						ans = max(ans, sec_home);
				}
			}
		}
		cout << "#" << i + 1 << " " << ans << '\n';
	}
	return 0;
}

void init() {
	memset(&city[0][0], 0, sizeof(city));
}

bool is_range(int r, int c) {
	return r >= 1 && r <= n_of_city && c >= 1 && c <= n_of_city;
}

int operating_cost(int depth, int r, int c) {
	return depth * depth + (depth - 1) * (depth - 1);
}

int securitied_house(int depth, int r, int c) {
	int count = 0;

	for (int i = r - 1, k = depth - 2; i >= r - (depth - 1); i--, k--) {
		for (int j = c - k; j <= c + k; j++) {
			if (is_range(i,j) == IN_RANGE && city[i][j] == true)
				count++;
		}
	}
	
	for (int i = c - (depth - 1); i <= c + (depth - 1); i++) {
		if (is_range(r, i) == IN_RANGE && city[r][i] == true)
			count++;
	}

	for (int i = r + 1, k = depth - 2; i <= r + (depth - 1); i++, k--) {
		for (int j = c - k; j <= c + k; j++) {
			if (is_range(i, j) == IN_RANGE && city[i][j] == true)
				count++;
		}
	}

	return count;
}