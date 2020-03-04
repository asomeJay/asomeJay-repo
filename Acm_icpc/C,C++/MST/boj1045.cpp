/* µµ·Î */

#include <iostream>
#include <cstring>
#include <vector>

#define MAX_P 50
#define MAX_M 1000

using namespace std;

class rode {
public:
	int parent[MAX_P];
	rode(){
		for (int i = 0; i < MAX_P; i++) 
			this->parent[i] = -1;
	}

	int find(int a) {
		if (this->parent[a] < 0) return a;
		return parent[a] = find(parent[a]);
	}

	bool uni(int a, int b) {
		int pa = find(a);
		int pb = find(b);
		if (pa == pb) return false;
		else
			this->parent[pb] = pa;
		return true;
	}
};

int main(void) {
	int N, M, r1 = 0, r2[MAX_P] = { 0, };
	bool is_used[MAX_M] = { 0 };
	vector<pair<int, int>> r;

	cin >> N >> M;
	getchar();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (getchar() == 'Y' && j > i)
				r.push_back({ i,j });
		}
		getchar();
	}

	rode t;
	for (int i = 0; i < r.size() && r1 < N - 1; i++) {
		int u = r[i].first, v = r[i].second;
		if (t.uni(u, v)) {
			is_used[i] = true;
			r1++;
			r2[u]++; r2[v]++;
		}
	}

	if (r1 < N - 1) {
		cout << -1 << '\n';
		return 0;
	}

	for (int i = 0; i < r.size() && r1 < M; i++) {
		int u = r[i].first, v = r[i].second;
		if (!is_used[i]) {
			is_used[i] = true;
			r1++;
			r2[u]++; r2[v]++;
		}
	}

	if (r1 < M) {
		cout << -1 << '\n';
		return 0;
	}

	for (int i = 0; i < N; i++) {
		cout << r2[i] << " ";
	}

	return 0;
}