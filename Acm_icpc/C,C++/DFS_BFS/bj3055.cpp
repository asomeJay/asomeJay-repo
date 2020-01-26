/* 탈출 : 고슴도치가 물 차는 땅 피해서 자기 친구인 비버 굴로 도망감 */

#include <iostream>
#include <queue>

#define HEDGEHOG -1
#define ROCK 2
#define EMPTY 1
#define WATER 0

#define MAX_MAP 51
#define UNVISIT 0
#define VISIT 1
#define OUT_OF_RANGE 0
#define IN_RANGE 1

using namespace std;

/* 
Input : None
Output : Extense the water's region(by one turn) 
*/
void water_extension();

/* Input : 행과 열
   Output : 좌표값이 범위 안인지 밖인지 */
bool is_range(int r_, int c_);

/* Input : None
   Output : 진행가능하면 true, 진행불가능하면 false */
bool bfs();

pair<int, int> hedgehog;
pair<int, int> beaver;

int water[MAX_MAP][MAX_MAP];
int map[MAX_MAP][MAX_MAP];
bool is_visit[MAX_MAP][MAX_MAP];
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0,1,0,-1 };
int r, c, mini;

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
			case 'D' : 
				beaver.first = i;
				beaver.second = j;
				break;
			case 'S' : 
				is_visit[i][j] = VISIT;
				hedgehog.first = i;
				hedgehog.second = j;
				break;
			case '.':
				map[i][j] = EMPTY;
				break;
			case '*':
				water[i][j] = 1;
				break;
			case 'X' : 
				map[i][j] = ROCK;
				break;
			default : 
				cout << "???";
			}
		}
	}

	while (1) {
		mini++;
		if (!bfs()) {
			cout << "KAKTUS" << '\n';
			return 0;
		}
		
		if (is_visit[beaver.first][beaver.second] == VISIT) break;
	}

	cout << mini << '\n';

	return 0;
}

void water_extension() {
	queue<pair<int, int>> a;
	int i, j, n_r, n_c, t_r, t_c;

	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			if (water[i][j] == 1)
				a.push(make_pair(i, j));
		}
	}

	while (!a.empty()) {
		n_r = a.front().first;
		n_c = a.front().second;
		a.pop();

		for (i = 0; i < 4; i++) {
			t_r = n_r + dr[i];
			t_c = n_c + dc[i];

			if (is_range(t_r, t_c) == OUT_OF_RANGE || water[t_r][t_c] == 1 || map[t_r][t_c] == ROCK) continue;
			if (t_r == beaver.first && t_c == beaver.second || is_visit[t_r][t_c] == VISIT) continue;
				water[t_r][t_c] = 1;
		}
	}

}

bool is_range(int r_, int c_) {
	if (r_ >= 1 && r_ <= r && c_ >= 1 && c_ <= c)
		return IN_RANGE;
	return OUT_OF_RANGE;
}

bool bfs() {
	int i, j, n_r, n_c, t_r, t_c, flag = 0;
	queue<pair<int,int>> h_place; // beaver place; 

	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			if (is_visit[i][j] == VISIT) {
				h_place.push(make_pair(i, j));
			}
		}
	}

	water_extension();

	while (!h_place.empty()) {
		n_r = h_place.front().first;
		n_c = h_place.front().second;
		h_place.pop();

		for (i = 0; i < 4; i++) {
			t_r = n_r + dr[i];
			t_c = n_c + dc[i];
			if (is_range(t_r, t_c) == OUT_OF_RANGE) continue;  // 범위 밖이면 체크안해
			if (map[t_r][t_c] == ROCK || water[t_r][t_c] == 1) continue; // 돌이거나 물찼으면 체크안해 
			if (is_visit[t_r][t_c] == VISIT) continue; // 이미 방문한 곳이면 최단거리가 아닐거니까 방문안해 

			
			is_visit[t_r][t_c] = VISIT;
			map[t_r][t_c] = map[n_r][n_c] + 1;
			flag = 1;

		}
	}
	return flag == 1;
}