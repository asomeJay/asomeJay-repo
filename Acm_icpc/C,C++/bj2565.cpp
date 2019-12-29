/* 전깃줄 제거하기 DP: */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n_of_elec;
vector<pair<int, int>> A_B;

bool comp(const pair<int, int>& a, const pair<int, int>& b) {
	return a.first < b.first;
}

int main(void) {
	int i, j, k, max, ans; cin >> n_of_elec;
	int dp[501];
	A_B.push_back(make_pair(-10, -10));

	for (i = 1; i <= n_of_elec; i++) {
		scanf("%d %d", &j, &k);
		A_B.push_back(make_pair(j, k));
		dp[i] = 1;
	}
		

	sort(A_B.begin(), A_B.end(), comp);

	ans = 1;
	for (i = 2; i <= n_of_elec; i++) {
		max = 0;
		for (j = 1; j < i; j++) {
	//		printf("A_B[%d].second : %d   ///   A_B[%d].second : %d\n", i, A_B[i].second, j, A_B[j].second);
			if (A_B[i].second > A_B[j].second) {
				if (max < dp[j])
					max = dp[j];
			}
		}

		dp[i] = max + 1;
		if (ans < dp[i]) {
			ans = dp[i];
		}
	}
	
	printf("%d\n", n_of_elec - ans);

	return 0;
}