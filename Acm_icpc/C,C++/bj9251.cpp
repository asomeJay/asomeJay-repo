/* LCS 문제 */

#include <iostream>
#include <algorithm>

using namespace std;

int dp[1001][1001];

int main(void) {
	int i, j;
	string a, b;
	cin >> a >> b;

	dp[0][0] = 0;

	for (i = 1; i <= a.size(); i++) 
		dp[0][i] = 0;
	
	for (j = 1; j <= b.size(); j++) 
		dp[j][0] = 0;
	
	for (i = 1; i <= a.size(); i++) {
//		printf("%d\n", b[0] == a[i - 1]);
		if (b[0] == a[i-1]) 
			dp[1][i] = 1;
		else 
			dp[1][i] = dp[1][i - 1];
		
	}

	for (i = 1; i <= b.size(); i++) {
		if (a[0] == b[i - 1])
			dp[i][1] = 1;
		else
			dp[i][1] = dp[i - 1][1];
	}
	//행에 a 열에 b

	for (i = 2; i <= b.size(); i++) {
		for (j = 2; j <= a.size(); j++) {
			if (b[i-1] == a[j-1]) 
				dp[i][j] = dp[i - 1][j - 1] + 1;
			
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	/*
	for (i = 0; i <= b.size(); i++) {
		for (j = 0; j <= a.size(); j++) {
			printf("%d ", dp[i][j]);
		}

		printf("\n");
	}*/

	printf("%d\n", dp[b.size()][a.size()]);

	return 0;
}