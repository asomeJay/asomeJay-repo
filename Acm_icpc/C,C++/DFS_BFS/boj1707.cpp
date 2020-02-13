/* 이분 그래프 */

#include <iostream>
#include <queue>

#define MAX_VERTEX 20010
#define MAX_EDGE 200010
#define UNVISIT 0
#define VISIT 1
#define RED 2
#define BLUE 3

using namespace std;

int V, E;
int is_visit[MAX_VERTEX];

vector<int> graph[MAX_VERTEX];

void init();
bool bfs(int src);
void print_debug();

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t_of_case, source, arrive;

	cin >> t_of_case;

	for (int i = 1; i <= t_of_case; i++) {
		init();
		cin >> V >> E;
		for (int j = 1; j <= E; j++) {
			cin >> source >> arrive;
			graph[source].push_back(arrive);
			graph[arrive].push_back(source);
		}

		int j;
		for (j = 1; j <= V; j++) {
//			cout << j << endl;
			if (bfs(j) == false) break;
		}

		for (int k = 1; k <= V; k++) {
			if (is_visit[k] == UNVISIT)
				j = 0;
		}
		
		if (j > V)
			cout << "YES\n";
		else
			cout << "NO\n";
//		print_debug();

	}
	return 0;
}

void init() {
	fill(&is_visit[0], &is_visit[MAX_VERTEX], UNVISIT);
	for (int i = 1; i<= V; i++) 
		graph[i].clear();
	V = E = 0;
	
}

bool bfs(int src) {
	queue<int> a;
	int cur_color;
	if (is_visit[src] == UNVISIT)
		cur_color = BLUE;
	else
		cur_color = is_visit[src];
	a.push(src);

	is_visit[src] = cur_color;
	int i, tc, new_node;
	while (!a.empty()) {
		new_node = a.front();
		if (is_visit[new_node] == BLUE) cur_color = RED;
		else if (is_visit[new_node] == RED) cur_color = BLUE;

		a.pop();

		for (i = 0; i < graph[new_node].size(); i++) {
			tc = graph[new_node][i];
			if (is_visit[tc] == UNVISIT) {
				is_visit[tc] = cur_color;
				a.push(tc);
			}
			else if (is_visit[tc] != cur_color) {
				return false;
			}
		}
	}
	return true;
}

void print_debug() {
	int i, j;
	cout << "Pring Debug Start\n";

	for (i = 1; i <= V; i++) {
		for (j = 0; j < graph[i].size(); j++) {
			cout << graph[i][j] << " ";
			if(is_visit[graph[i][j]] == RED)
				cout << "RED  \n";
			else if (is_visit[graph[i][j]] == BLUE)
				cout << "BLUE  \n";
			
		}
		cout << '\n';
	}
}