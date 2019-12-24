/* 백트랙킹 : 스타트와 링크 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int dp[30][30];
int long_dp[300]; // 지금까지 선택된애 

void dfs(int row, int);
int personnel, n, ans, mini;
void long_clean();

int main(void) {
	int i, j; cin >> n;

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			scanf("%d", &dp[i][j]);
		}
	}

	mini = 900;
	personnel = (n / 2) ;

	for (i = 1; i <= n; i++) {	// n이 뭐냐면.... n이 전체 열의 개수임. 
		long_clean();

		long_dp[i] = 1; 
		dfs(2, i);
	}

	printf("%d\n", mini);

	return 0;
}

void dfs(int row, int start_point) {
	int i, j;
	vector<int> team_start, team_link;

	if (row > personnel) {
		int sum, stat_start, stat_link;
		sum = 0;

		for (i = 1; i <= n; i++) {
			if (long_dp[i] != 0)
				team_start.push_back(i);
			else
				team_link.push_back(i);
		}

		stat_start = 0; stat_link = 0;

		for (i = 0; i < team_start.size(); i++) {
			for (j = i+1; j < team_start.size(); j++) {
				stat_start += dp[team_start[i]][team_start[j]] + dp[team_start[j]][team_start[i]];
				stat_link += dp[team_link[i]][team_link[j]] + dp[team_link[j]][team_link[i]];
			}
		}

		ans = abs(stat_start - stat_link);
		mini = min(ans, mini);

		return;
	}

	for (i = start_point + 1; i <= n; i++) {
			long_dp[i] = 1;
			dfs(row + 1, i);
			long_dp[i] = 0;
	}
}

void long_clean() {
	int i;
	for (i = 0; i < 300; i++) {
		long_dp[i] = 0;
	}
}
