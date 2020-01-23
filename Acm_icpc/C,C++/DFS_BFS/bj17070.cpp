/* 파이프 옮기기 */

#include <iostream>

#define CANT 0
#define CAN 1
#define D 2
#define H 3
#define V 4
#define WALL 1

using namespace std;

bool is_range(int, int, int);
bool is_wall(int r, int c, int target);
bool can_go(int r, int c, int target);
void recursive(int r, int c, int);

int house[17][17];
int N, counti;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int i, j;
	cin >> N;
	
	for (i = 1; i <= N; i++) 
		for (j = 1; j <= N; j++) 
			cin >> house[i][j];

	recursive(1, 2, H);
	cout << counti << endl;

	return 0;
}

bool is_range(int r, int c, int target) {
	if (r < 1 || r > N || c < 1 || c > N) return CANT;
	switch (target) {
	case D:
		if (c + 1 > N || r + 1 > N) return CANT;
		break;
	case H:
		if (c + 1 > N) return CANT;
		break;
	case V:
		if (r + 1 > N) return CANT;
		break;
	}
	
	return CAN;
}

bool is_wall(int r, int c, int target) {
	switch (target) {
	case D:
		if (house[r][c+1] == WALL || \
			house[r+1][c+1] == WALL || \
			house[r+1][c] == WALL) return CANT;
		break;
	case H:
		if (house[r][c+1] == WALL) return CANT;
		break;
	case V:
		if (house[r + 1][c] == WALL) return CANT;
		break;
	}
	return CAN;
}

bool can_go(int r, int c, int direction) {
	if (is_range(r, c, direction) == CANT) return CANT;
	if (is_wall(r, c, direction) == CANT) return CANT;
	return CAN;
}

void recursive(int r, int c, int cur_direction) {
	if (r == N && c == N) counti++;
	switch (cur_direction) {
	case D:
		if (can_go(r, c, H) == CAN)
			recursive(r, c + 1, H);
		if (can_go(r, c, D) == CAN)
			recursive(r + 1, c + 1, D);
		if (can_go(r, c, V) == CAN)
			recursive(r + 1, c, V);
		break;
	case H :
		if (can_go(r, c, H) == CAN)
			recursive(r, c + 1, H);
		if (can_go(r, c, D) == CAN)
			recursive(r + 1, c + 1, D);
		break;
	case V:
		if (can_go(r, c, D) == CAN)
			recursive(r + 1, c + 1, D);
		if (can_go(r, c, V) == CAN)
			recursive(r + 1, c, V);
		break;
	}
}