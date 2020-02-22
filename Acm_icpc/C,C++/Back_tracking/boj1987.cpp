/* ¾ËÆÄºª */

#include <iostream>
#include <algorithm>

#define IN_RANGE 1
#define OUT_RANGE 0
#define MAX_BOARD 20 + 1

using namespace std;

int ROW, COL, ANS;
int board[MAX_BOARD][MAX_BOARD];
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };
bool alpha[27];

bool is_range(int r, int c);
void board_go(int r, int c, int);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int i, j, k, nr, nc;
	char t_board;
	cin >> ROW >> COL;
	for (i = 1; i <= ROW; i++) {
		for (j = 1; j <= COL; j++) {
			cin >> t_board;
			board[i][j] = t_board;
		}
	}

	alpha[board[1][1] - 'A'] = true; 
	board_go(1, 1, 1);
	
	cout << ANS;
	return 0;
}

bool is_range(int r, int c) {
	return 1 <= r && r <= ROW && 1 <= c && c <= COL;
}

void board_go(int r, int c, int value) {
	int nr, nc, i, j, alphabet;

	ANS = max(ANS, value);

	for (i = 0; i < 4; i++) {
		nr = r + dr[i];
		nc = c + dc[i];
		if (is_range(nr, nc)) {
			alphabet = board[nr][nc] - 'A';

			if (alpha[alphabet] != true) {
				alpha[alphabet] = true;
				board_go(nr, nc, value + 1);
				alpha[alphabet] = false;
			}
		}
	}
}