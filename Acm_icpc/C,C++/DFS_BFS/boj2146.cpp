/* 다리 만들기 */

#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <cstring>

#define MAX_MAP 100+1
#define OUT_RAGNE 0
#define IN_RANGE 1
#define MAX_INT 2100000000

using namespace std;

int N, mini;
int map[MAX_MAP][MAX_MAP], map_name;

int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

void land_name(int, int);
bool is_range(int, int);
void print_debug(int, int);
int bridge_distance(int);
//int bridge(int, int, int, int, int);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> N;

	int i, j, k;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) 
			cin >> map[i][j];
	}

	map_name++;
	mini = MAX_INT;
	
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			if (map[i][j] == 1) {
				map_name++;
				land_name(i, j);
			}
		}
	}
	/*
	cout << endl;
	for (int k = 2; k <= map_name; k++) {
		cout << k << " " << endl;
		for (int m = 0; m < land_cord[k].size(); m++) {
			cout << land_cord[k][m].first  << " " << land_cord[k][m].second << "///" ;
		}
		cout << endl;
	}*/
	
	for (i = 2; i <= map_name; i++) {
		mini = min(mini, bridge_distance(i));
	}	
	
	cout << mini << '\n';
	return 0;
}

void land_name(int r, int c) {
	int i, j, nr, nc, tr, tc;
	stack<pair<int,int>> s;
	s.push(make_pair(r, c));

	map[r][c] = map_name;

	while (!s.empty()) {
		nr = s.top().first;
		nc = s.top().second;
		s.pop();

		for (i = 0; i < 4; i++) {
			tr = nr + dr[i];
			tc = nc + dc[i];
			if (is_range(tr, tc) == IN_RANGE && map[tr][tc] == 1) {
				map[tr][tc] = map_name;
				s.push(make_pair(tr, tc));
			}
		}
	}
}

bool is_range(int r, int c) {
	return r >= 1 && r <= N && c <= N && c >= 1;
}

void print_debug(int r, int c) {
	int i, j;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

int bridge_distance(int start) {
	int i, j, k, nr, nc, tr, tc, q_size;
	queue<pair<int, int>> q;
	int result = 0;
	bool is_visit[MAX_MAP][MAX_MAP] = { 0, };

	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			if (map[i][j] == start) {
				q.push(make_pair(i, j));
				is_visit[i][j] = true;
			}
		}
	}
	
	while (!q.empty()) {
		result++;

		q_size = q.size();

		for (i = 0; i < q_size; i++) {
			nr = q.front().first;
			nc = q.front().second;
			q.pop();

			for (j = 0; j < 4; j++) {
				tr = nr + dr[j];
				tc = nc + dc[j];

				if (is_range(tr, tc) == IN_RANGE) {
					if (map[tr][tc] != 0 && map[tr][tc] != start) {
						return result-1;
					}

					if (is_visit[tr][tc] == 0 && map[tr][tc] == 0) {
						is_visit[tr][tc] = true;
						q.push(make_pair(tr, tc));
					}
				}
			}
		}
	}
}