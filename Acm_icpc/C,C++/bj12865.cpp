/* 0-1 Knapsack PB */

#include <iostream>
#include <array>
#include <algorithm>
#include <vector>

using namespace std;

int n_product, can_weight;
int dp[101][100001];

int main(void) {
	int i, j, t_i, t_j;
	cin >> n_product >> can_weight;

	vector<pair<int, int>> v_item;
	v_item.push_back(make_pair(0, 0));
	for (i = 1; i <= n_product; i++) {
		scanf("%d %d", &t_i, &t_j);
		v_item.push_back(make_pair(t_i, t_j));
	}

	sort(v_item.begin(), v_item.end());

	for (i = 0; i <= n_product; i++) 
		dp[i][0] = 0;
	
	for (i = 0; i <= can_weight; i++)
		dp[0][i] = 0;

	for (i = 1; i <= n_product; i++) {
		for (j = 1; j <= can_weight; j++) {
			if (v_item[i].first > j)
				dp[i][j] = dp[i-1][j];
			else {
				dp[i][j] = max(dp[i-1][j], v_item[i].second + dp[i-1][j - v_item[i].first]);
			}
		}
	}
	/*
	for (i = 0; i <= n_product; i++) {
		for (j = 0; j <= can_weight; j++) {
			printf("%d   ", dp[i][j]);
		}
		printf("\n");
	}*/

	printf("%d\n", dp[n_product][can_weight]);

	return 0;
}