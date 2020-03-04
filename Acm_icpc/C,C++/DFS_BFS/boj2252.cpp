/* 줄 세우기 */

#include <iostream>
#include <vector>

#define MAX_STUDENT 32000 + 1
#define MAX_COMP 100000 + 1

using namespace std;

int N, M;
vector<int> priority[MAX_STUDENT];
bool is_used[MAX_STUDENT];
bool parent[MAX_STUDENT];

void print(int );

int main(void) {
	int lv, rv;

	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		cin >> lv >> rv;
		parent[lv] = true;
		priority[rv].push_back(lv);
	}

	for (int i = 1; i <= N; i++) {
		if (parent[i] == false) {
			print(i);
		}
	}

	for (int i = 1; i <= N; i++) {
		if (is_used[i] == true) continue;
		cout << i << " ";
	}

	return 0;
}

void print(int point) {
	for (int i = 0; i < priority[point].size(); i++) {
		if (is_used[priority[point][i]] == true) continue;

		is_used[priority[point][i]] = true;
		int r = priority[point][i];
		
		print(priority[point][i]);
		cout << r << " ";
	}
}