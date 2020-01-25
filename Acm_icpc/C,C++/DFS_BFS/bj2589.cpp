/* 보물섬 */

#include <iostream>
#include <string>
#include <queue>

#define MAX_MAP 52
#define L 1
#define W 0
#define OUT_OF_RANGE 1
#define IN_RANGE 0
#define N 0 
#define E 1
#define S 2
#define W 3
#define UNVISIT 0
#define VISIT 1

using namespace std;

/* 매개변수로 들어온 좌표가 지도의 범위 안에 있는가?
  있다면 True 아니라면 False를 return 한다. */
bool is_range(pair<int, int>);

/* 매개변수로 시작지점을 받는다. 그 점에서부터 모든 곳으로 가는 recursive call을 한다.
  제일 긴 거리가 측정될 때마다 전역변수인 f_p를 그 좌표로 갱신하고 maxi로 그 거리값을
  갱신한다. */
void bfs(pair<int, int>);
void printt();
void init();

pair<int, int> s_p; // s_p : start_point
pair<int, int> f_p; // f_p : final_point
int map[MAX_MAP][MAX_MAP];
int is_visit[MAX_MAP][MAX_MAP];
int depth[MAX_MAP][MAX_MAP];
int r, c, maxi;
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0 ,-1 };


int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int i, j;
	char ccc;

	cin >> r >> c;
	
	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			cin >> ccc;
			switch (ccc) {
			case 'W':
				map[i][j] = W;
				break;
			case 'L':
				map[i][j] = L;
				break;
			}
		}
	}

	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			if (map[i][j] == L) {
				init();
				is_visit[i][j] = VISIT;
				bfs(make_pair(i, j));
			}
		}
	}

	cout << maxi<<'\n';
	return 0;
}


bool is_range(pair<int, int> a) {
	if (a.first >= 1 && a.first <= r && a.second >= 1 && a.second <= r) {
		return IN_RANGE;
	}
	return OUT_OF_RANGE;
}

// c_p : current_point
void bfs(pair<int, int>s_p_) {
	int n_r, n_c, i, t_d, t_r, t_c;
	pair<int, int> t;

	queue<pair<int, int>> cord;

	cord.push(s_p_);

	while (!cord.empty()) {
		n_r = cord.front().first;
		n_c = cord.front().second;
		cord.pop();

		for (i = 0; i < 4; i++) {
			t_r = n_r + dr[i];
			t_c = n_c + dc[i];

			t = make_pair(t_r, t_c);
			
			if (is_range(t) == OUT_OF_RANGE || map[t_r][t_c] == W || is_visit[t_r][t_c] == VISIT) 
				continue;

			//if (is_visit[t_r][t_c] == UNVISIT || is_visit[t_r][t_c] > is_visit[n_r][n_c] + 1) {
//			if (is_visit[t_r][t_c] == UNVISIT) {
			is_visit[t_r][t_c] = VISIT;
			//is_visit[t_r][t_c] = is_visit[n_r][n_c] + 1;
			depth[t_r][t_c] = depth[n_r][n_c] + 1;
			cord.push(t);
			//xprintt();
			maxi = max(maxi, depth[t_r][t_c]);
//			}
		}
	}
}

void printt() {
	int i, j;
	cout << endl;
	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			cout << is_visit[i][j] << " ";
		}
		cout << endl;
	}
}

void init() {
	int i, j;
	memset(is_visit, 0, sizeof(is_visit));
	memset(depth, 0, sizeof(depth));
}