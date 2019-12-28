/* 가장 긴 증가하는 부분 수열 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

bool comp(const pair<int, int>& a, const pair <int, int>& b) {
	return a.first < b.first;
}

int binary_search_pos(int left, int right, int target);
int real[1000001];
vector<int> seq;

int main(void) {
	int s_of_seq, i, j, k; scanf("%d", &s_of_seq);
	//vector<pair<int,int>> seq;
	int avail_pos[1000001];

	
	seq.push_back(-1000000001);

	for (i = 1; i <= s_of_seq; i++) {
		scanf("%d", &k);
		real[i] = k;
		if (seq.back() < k) {
			seq.push_back(k);
			avail_pos[i] = seq.size() - 1;
		}

		else {
			auto it = lower_bound(seq.begin(), seq.end(), k);
			*it = k;
			avail_pos[i] = binary_search_pos(1, seq.size() - 1, *it);
		}
	}
	printf("%d\n", seq.size() - 1);
	int count = seq.size() - 1;
	stack<int> s;
	for (i = s_of_seq; i > 0; i--) {
		if (count == avail_pos[i]) {
			s.push(real[i]);
			count--;
		}
	}

	while (!s.empty()) {
		printf("%d ", s.top());
		s.pop();
	}

	return 0;
}
int binary_search_pos(int left, int right, int target) {
	int middle;
	while (left < right) {
		middle = (left + right) / 2;
		if (seq[middle] == target) return middle;
		else if (seq[middle] > target) {
			right = middle - 1;
		}
		else {
			left = middle + 1;
		}
	}
}
