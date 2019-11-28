/* DP : ¼è¸·´ë±â */

#include <iostream>

using namespace std;

int dp[50000];

int main(void) {
	int i, j, k, top;
	string s;
	cin >> s;
	top = -1;
	for (i = 0; i < s.size(); i++) {
		if (s[i] == '(') {
			if ((i < s.size() - 1) && s[i + 1] == ')') {
				i++;
				for (j = 0; j <= top; j++)
					dp[j]++;
			}
			else {
				dp[++top] += 1;

			}
			
		}
		else if (s[i] == ')') {
			top--;
		}
	}
	for (i = 1; dp[i] != 0; i++)
		dp[i] += dp[i - 1];
	
	cout << dp[i - 1] << endl;
	return 0;
}