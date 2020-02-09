/* 체스판 다시 칠하기 */

#include <iostream>
#include <string>
#include <algorithm>

#define MAX_MAP 51

using namespace std;

int ROW, COL;
int map[MAX_MAP][MAX_MAP];
int white_first[8][8] =
{ {'W','B','W','B','W','B','W','B'},
{ 'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W' },
{'W','B','W','B','W','B','W','B'},
{ 'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W' },
{'W','B','W','B','W','B','W','B'},
{ 'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W' },
{'W','B','W','B','W','B','W','B'},
{ 'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W' },
};

int black_first[8][8] = {
	{ 'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W' },
	{'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B'},
	{ 'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W' },
	{'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B'},
	{ 'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W' },
	{'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B'},
	{ 'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W' },
	{'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B'},
};

pair<int,int> dp_map[MAX_MAP][MAX_MAP];
void print_debug();
int white_map(int, int);
int black_map(int, int);

int paint;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> ROW >> COL;
	int i, j, k, white, black;
	paint = 2000000;
	string tt;

	for (i = 1; i <= ROW; i++) {
		cin >> tt;
		for (j = 0; j < tt.size(); j++) {
			map[i][j + 1] = tt[j];
		}
	}

	for (i = 1; i + 7 <= ROW; i++) {
		for (j = 1; j + 7 <= COL; j++) {
			paint = min(paint, black_map(i, j));
			paint = min(paint, white_map(i, j));
		}
	}
	cout << paint << '\n';

	return 0;
}

void print_debug() {
	int i, j;

	for (i = 1; i <= ROW; i++) {
		for (j = 1; j <= COL; j++) {
			cout << "["<<(char)map[i][j] << "]"<< " ";
		}
		cout << endl;
	}
}

int white_map(int sr, int sc) {
	int i, j, cnt;
	cnt = 0;
	for (i = sr; i <= sr + 7; i++) {
		for (j = sc; j <= sc + 7; j++) {
			if (map[i][j] != white_first[i-sr][j-sc])
				cnt++;
		}
	}

	return cnt;
}

int black_map(int sr, int sc) {
	int i, j, cnt;
	cnt = 0;
	for (i = sr; i <= sr + 7; i++) {
		for (j = sc; j <= sc + 7; j++) {
			if (map[i][j] != black_first[i - sr][j - sc]) {
				cnt++;
			}
				
		}
	}
	return cnt;
}