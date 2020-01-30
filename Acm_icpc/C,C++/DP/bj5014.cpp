/* 스타트링크 
: 엘리베이터 문제 */

#include <iostream>
#include <queue>

#define MAX_DP 1000010

using namespace std;

int F, G, S, U, D;
int dp[MAX_DP];
// S + xU -yD = G
// yD = xU + S - G;
int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> F >> S >> G >> U >> D;

	queue<int> s;

	s.push(S);
	dp[S] = 0;

	int temp;

	while (!s.empty()) {
		temp = s.front(); s.pop();
		
		if (temp + U <= F && dp[temp + U] == 0 && temp + U != S) {
			s.push(temp + U);
			dp[temp + U] = dp[temp] + 1;
		}

		if (temp - D > 0 && dp[temp-D] == 0 && temp - D != S) {
			s.push(temp - D);
			dp[temp - D] = dp[temp] + 1;
		}
	}

	if (G != S && dp[G] == 0) {
		cout << "use the stairs" << '\n';
	}
	else {
		cout << dp[G] << '\n';
	}

	return 0;
}

