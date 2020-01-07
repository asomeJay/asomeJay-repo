/* ¼ø¿­ */

#include <iostream>

using namespace std;

void dfs(int depth, int, int[], bool[]);

int main(void) {
	int n, i, j;
	int l[9];
	bool visit[9];

	cin >> n;

	for (i = 1; i <= n; i++) {
		visit[i] = 1;
		l[1] = i;
		dfs(2, n, l, visit);
		visit[i] = 0;
	}

	return 0;
}

void dfs(int depth, int limit, int list[], bool visit[]) {
	int i;

	if (depth > limit) {
		for (i = 1; i <= limit; i++) {
			printf("%d ", list[i]);
		}
		printf("\n");
		return;
	}

	for (i = 1; i <= limit; i++) {
		if (visit[i] != 1) {
			visit[i] = 1;
			list[depth] = i;
			dfs(depth+1, limit, list, visit);
			visit[i] = 0;
		}
	}
}