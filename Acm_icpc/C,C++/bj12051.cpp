/* 가장 긴 증가하는 부분 수열 2 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int seq[1000001];
vector<int> dp_seq;

int main(void) {
	int i, j, s_size, max, ans; cin >> s_size;

	dp_seq.push_back(-1);

	for (i = 1; i <= s_size; i++) {
		scanf("%d", &seq[i]);
		if (dp_seq.back() < seq[i]) {
			dp_seq.push_back(seq[i]);
		}

		else {
			auto temp = lower_bound(dp_seq.begin(), dp_seq.end(),
				seq[i]);
			*temp = seq[i];
		}
	}
		
	printf("%d\n", dp_seq.size() - 1);

	return 0;
}
