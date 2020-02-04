/* 네트워크 연결 */

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_COM 1001
#define MAX_LINE 100001
#define MAX_COST 10000
#define SAME -1
#define DIFF -2

using namespace std;

class edge {
public:
	int node[2];
	int distance;

	edge(int a, int b, int dist) {
		this->node[0] = a;
		this->node[1] = b;
		this->distance = dist;
	}

	bool operator <(edge& e) {
		return this->distance < e.distance;
	}
};

int find_parent(int a);
int union_parent(int a, int b);

int N, M;
int parent[MAX_COM];
vector<edge> com;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int i, j, k, a, b;

	cin >> N >> M;

	for (i = 1; i <= M; i++) {
		cin >> a >> b >> k;
		com.push_back(edge(a, b, k));
	}

	for (i = 1; i <= N; i++) {
		parent[i] = i;
	}

	sort(com.begin(), com.end());
	
	int sum = 0, par;
	for (i = 0; i < com.size(); i++) {
		if ((par = union_parent(com[i].node[0], com[i].node[1])) != SAME) {
			sum += com[i].distance;
		}
	}

	cout << sum << '\n';

	return 0;

}

int find_parent(int a) {
	if (a == parent[a]) return a;
	else
		return parent[a] = find_parent(parent[a]);
}

int union_parent(int a, int b) {
	int aa = find_parent(a);
	int bb = find_parent(b);

	if (aa == bb) return SAME;
	else {
		parent[aa] = bb;
		find_parent(a);
		return DIFF;
	}

}