/* 디저트 카페 */
#include <iostream>
#include <algorithm>
#include <climits>

#define MAX_CAFE 25
#define MAX_ROTATE 4
#define MAX_DESSERT 101
#define LEFT_DOWN 3
#define RIGHT_DOWN 2
#define LEFT_UP 0
#define RIGHT_UP 1
#define NOT 5
#define OUT_OF_RANGE 0
#define IN_RANGE 1

using namespace std;

int r[4] = {-1,-1,1,1 };
int c[4] = {-1, 1, 1, -1 };
int haved_dessert[MAX_DESSERT];
int haved_dir[MAX_ROTATE];
int dessert_cafe[MAX_CAFE][MAX_CAFE];
int maxi, N;

/* 매개변수로 들어온 방향의 반대방향을 return 해준다. */
int opposite_dir(int dir);
/* 매개변수로 들어온 row와 column 값이 정상적인 범위 안 인지 체크한다. */
bool is_range(int r, int c);
/* 각 테스트를 할 때마다 배열을 초기화해줘야 한다.*/
void init();
/* 이게 리얼 찐 함수임 */
void dfs(int s_r, int s_c, int c_r, int c_c, int dir, int cur_cnt);
/* 같은 디저트인지 체크하기 
    같은 디저트면 true, 다르면 false를 return 한다. */
bool same_dessert(int a_r, int a_c, int b_r, int b_c);

int main(void) {
	int t; cin >> t;
	int i, j, k;
	for (k = 1; k <= t; k++) {
		init();
		cin >> N;
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++) {
				cin >> dessert_cafe[i][j];
			}
		}


		/* LEFT_DOWN으로 가는 케이스만 고려해줄 것이다. 어차피 빙빙 돌아서
		원점으로 돌아오는 애 찾는건데 "왜 LEFT_DOWN만 고려해! RIGHT_DOWN도 고려해야지
		"라고 하면 "나는 그렇게 안할거다"라고 대답하고 싶다.*/

		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++) {
				/* 범위 벗어난 애들은 체크할 필요가 없어~~ */
				if (is_range(i + r[3], j + c[3]) == OUT_OF_RANGE) continue;
				/* 같은 디저트이면 생각할 필요도 없지 ~~ */
				if (same_dessert(i, j, i + r[3], j + c[3])) continue;

				/* 이 방향을 썻다~ 기록하고, 이 디저트 먹었어~ 저장한다 */
				haved_dir[LEFT_DOWN] = 1;
				haved_dessert[dessert_cafe[i][j]] = 1;
				haved_dessert[dessert_cafe[i + r[LEFT_DOWN]][j + c[LEFT_DOWN]]] = 1;

				dfs(i, j, i + r[LEFT_DOWN], j + c[LEFT_DOWN], LEFT_DOWN, 2);

				/* 이 방향과 디저트에 대한 dfs를 완료했으니
				원상복구를 해줘야 다른 애들이 이 방향과 이 디저트를 쓰지 */

				haved_dir[LEFT_DOWN] = 0;
				haved_dessert[dessert_cafe[i][j]] = 0;
				haved_dessert[dessert_cafe[i + r[LEFT_DOWN]][j + c[LEFT_DOWN]]] = 0;
			}
		}
		cout << "#" << k << " " << maxi << endl;
	}

	return 0;
}

int opposite_dir(int dir) {
	if (dir == LEFT_DOWN) return RIGHT_UP;
	if (dir == RIGHT_DOWN) return LEFT_UP;
	if (dir == LEFT_UP) return RIGHT_DOWN;
	if (dir == RIGHT_UP) return LEFT_DOWN;
}

bool is_range(int r, int c) {
	if (r <= 0 || r > N || c <= 0 || c > N) return OUT_OF_RANGE;
	return IN_RANGE;
}

void dfs(int s_r, int s_c, int c_r, int c_c, int dir, int cur_cnt) {
	if (c_r == s_r && c_c == s_c) {
		maxi = max(cur_cnt, maxi);
		return;
	}

	int i, n_r, n_c, dessert;

	for (i = 0; i < 4; i++) {
		/* 현재 진행방향의 정반대로 갈 필요가 없으니까. */
		if (i == opposite_dir(dir)) continue;
		if (i != dir && haved_dir[i] == 1) continue;

		n_r = c_r + r[i];
		n_c = c_c + c[i];
		if (is_range(n_r, n_c) == OUT_OF_RANGE) continue;

		dessert = dessert_cafe[n_r][n_c]; // 해당 칸의 디저트 종류는 무엇인가!

		if (n_r == s_r && n_c == s_c) dfs(s_r, s_c, n_r, n_c, i, cur_cnt);

		if (haved_dessert[dessert]) continue;

		haved_dir[i] = 1;
		haved_dessert[dessert] = 1;
		dfs(s_r, s_c, n_r, n_c, i, cur_cnt + 1);
		haved_dir[i] = 0;
		haved_dessert[dessert] = 0;
	}
}

void init() {
	fill(haved_dessert, haved_dessert + MAX_DESSERT, 0);
	fill(haved_dir, haved_dir + MAX_ROTATE, 0);
	fill(&dessert_cafe[0][0], &dessert_cafe[MAX_CAFE-1][MAX_CAFE], 0);
	maxi = -1;
}

bool same_dessert(int a_r, int a_c, int b_r, int b_c) {
	return dessert_cafe[a_r][a_c] == dessert_cafe[b_r][b_c];
}