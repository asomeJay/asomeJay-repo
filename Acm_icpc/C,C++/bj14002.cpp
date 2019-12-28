/* 가장 긴 증가하는 부분 수열 4 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int seq[1001][3];

int main(void) {
	int ans, ans_ind,ans_p, ans_i, max, i, j, k, n; scanf("%d", &n);
	stack<int> s;
	for (i = 1; i <= n; i++) {
		scanf("%d", &seq[i][0]);
		seq[i][1] = 1;
		seq[i][2] = 0;
	}
	// ans 는 길이를 말하는 거고, ans_p 는 참조한 이전 칸
	// ans_i는 마지막에 참조한 거 뭔지 저장함.
	ans = 1; ans_p = 0; ans_i = 1;
	for (i = 2; i <= n; i++) {
		max = 0;
		for (j = 1; j < i; j++) {
			if (seq[i][0] > seq[j][0]) {
				if (max < seq[j][1]) {
					max = seq[j][1];
					ans_p = j;
				}
			}
		}
		seq[i][1] = max + 1;
		seq[i][2] = ans_p;
		if (ans <= seq[i][1]) {
			ans_i = i;
			ans = seq[i][1];
		}
			
	}

	printf("%d\n", ans);
	do {
		s.push(seq[ans_i][0]);
		ans_i = seq[ans_i][2];

	} while (seq[ans_i][1] > 1);

	if(seq[ans_i][1] == 1)
		s.push(seq[ans_i][0]);

	while (!s.empty()) {
		printf("%d ", s.top());
		s.pop();
	}
	return 0;
}