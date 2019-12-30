/* 경로 찾기 */

#include <iostream>
#include <stack>

int graph[101][101];
int check[101][101];

int n_of_node;

void dfs(int v);

using namespace std;

int main(void) {
	int i, j;
	scanf("%d", &n_of_node);

	for (i = 1; i <= n_of_node; i++) {
		for (j = 1; j <= n_of_node; j++) 
			scanf("%d", &graph[i][j]);
	}

	for (i = 1; i <= n_of_node; i++) 
		dfs(i);
	
	for (i = 1; i <= n_of_node; i++) {
		for (j = 1; j <= n_of_node; j++) {
			printf("%d ", check[i][j]);
		}
		printf("\n");
	}

	return 0;
}

void dfs(int v) {
	stack<int> s;
	int node, i, j;
	bool is_visit[101] = { 0 };

	s.push(v);

	while (!s.empty()) {
		node = s.top();
		s.pop();
//		is_visit[node] = 1;

		for (i = 1; i <= n_of_node; i++) {
			if (is_visit[i] == 0 && graph[node][i] == 1) {
				s.push(i);
//				printf("%d  from : %d   to : %d\n",
//					v, node, i);
				is_visit[i] = 1;
			}
		}
	}

	for (i = 1; i <= n_of_node; i++) {
		if (is_visit[i]) {
			check[v][i] = 1;
		}
	}
	return;
}