/* 구슬 탈출 2 */

#include <iostream>
#include <algorithm>

#define N 0
#define E 1
#define S 2
#define W 3
#define CANT_MOVE 4
#define SAME 5
#define OK 1

#define MAX_BOARD 11
using namespace std;

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };
int ROW, COL, cnt = 100;
pair<int, int> red, blue, hole;
int move(int dir, char [MAX_BOARD][MAX_BOARD]);
void move_red(int dir, char[MAX_BOARD][MAX_BOARD]);
void move_blue(int dir, char[MAX_BOARD][MAX_BOARD]);
bool hole_in();
void tip(int, char[MAX_BOARD][MAX_BOARD]);


int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int i, j;
	char board[MAX_BOARD][MAX_BOARD];

	cin >> ROW >> COL;
	for (i = 1; i <= ROW; i++) {
		for (j = 1; j <= COL; j++) {
			cin >> board[i][j];
			if (board[i][j] == 'R') {
				red.first = i;
				red.second = j;
			}
			else if (board[i][j] == 'B') {
				blue.first = i;
				blue.second = j;
			}
			else if (board[i][j] == 'O') {
				hole.first = i;
				hole.second = j;
			}
		}
	}

	tip(0, board);
	if (cnt == 100)
		cnt = -1;
	cout << cnt;

	return 0;
}

int move(int dir, char t_board[MAX_BOARD][MAX_BOARD]) {
	switch (dir) {
	case N:
		if (red.first > blue.first) { // 파란공이 위에 있다.
			move_blue(N, t_board);
			move_red(N, t_board);
		}
		else {
			move_red(N, t_board);
			move_blue(N, t_board);
		}
		break;
	case E: 
		if (red.second < blue.second) {
			move_blue(E, t_board);
			move_red(E, t_board);
		}
		else {
			move_red(E, t_board);
			move_blue(E, t_board);
		}
		break;
	case S:
		if (red.first > blue.first) {
			move_red(S, t_board);
			move_blue(S, t_board);
		}
		else {
			move_blue(S, t_board);
			move_red(S, t_board);
		}
		break;
	case W:
		if (red.second < blue.second) {
			move_red(W, t_board);
			move_blue(W, t_board);
		}
		else {
			move_blue(W, t_board);
			move_red(W, t_board);
		}
		break;
	default : 
		cout << "ERROR AT MOVE\n";
	}

	return OK;
}

void tip(int depth, char t_board[MAX_BOARD][MAX_BOARD]) {
	if (depth >= 10) {
		return;
	}

	char cur_board[MAX_BOARD][MAX_BOARD];
	copy(&t_board[0][0], &t_board[MAX_BOARD - 1][MAX_BOARD], &cur_board[0][0]);
	
	int i, j, tr, tc, tbr, tbc;

	for (i = 0; i < 4; i++) {
		tr = red.first; tc = red.second;
		tbr = blue.first; tbc = blue.second;

		int t_move = move(i, cur_board);

		if (blue.first == hole.first && blue.second == hole.second) {
			copy(&t_board[0][0], &t_board[MAX_BOARD - 1][MAX_BOARD], &cur_board[0][0]);
			red.first = tr; red.second = tc;
			blue.first = tbr; blue.second = tbc;

			continue;
		}

		if (hole_in()) {
			cnt = min(cnt, depth + 1);
			red.first = tr; red.second = tc;
			blue.first = tbr; blue.second = tbc;
			return;
		}
		
		tip(depth + 1, cur_board);

		copy(&t_board[0][0], &t_board[MAX_BOARD - 1][MAX_BOARD], &cur_board[0][0]);
		red.first = tr; red.second = tc;
		blue.first = tbr; blue.second = tbc;
	}
}

bool hole_in() {
	if (hole.first == red.first && hole.second == red.second) {
		return true;
	}
	return false;
}

void move_red(int dir, char t[MAX_BOARD][MAX_BOARD]) {
	int i, j, r, c, tr, tc;
	r = red.first; c = red.second;
	t[r][c] = '.';
	while (true) {
		tr = r + dr[dir];
		tc = c + dc[dir];

		if (t[tr][tc] == '#' || t[tr][tc] == 'B')
			break;
		if (t[tr][tc] == 'O') {
			red.first = tr; red.second = tc;
			return;
		}
		r = tr; c = tc;
	}
	red.first = r; red.second = c;
	t[red.first][red.second] = 'R';
}

void move_blue(int dir, char t[MAX_BOARD][MAX_BOARD]) {
	int i, j, r, c, tr, tc;
	r = blue.first; c = blue.second;
	t[r][c] = '.';
	while (true) {
		tr = r + dr[dir];
		tc = c + dc[dir];

		if (t[tr][tc] == '#' || t[tr][tc] == 'R')
			break;
		if (t[tr][tc] == 'O') {
			blue.first = tr; blue.second = tc;
			return;
		}
		r = tr; c = tc;
	}
	blue.first = r; blue.second = c;
	t[blue.first][blue.second] = 'B';
}