/* 특이한 자석 */
/* 2하고 6만 맞닿아있다 */

#include <iostream>
#include <vector>

#define N 0
#define S 1
#define CW 1
#define COUNTER_CW -1

using namespace std;

pair<int, int> save[1001];		//first 돌아가야하는지 돌아가야하면 1, 아니면 0, 방향
int gear[1001][9];

int K;

bool opposite(int n_of_gear, int);
void turn_gear(int n_of_gear, int);

int main(void) {
	int T, i, j, k, l, n_of_magnet, d_of_magnet;
	scanf("%d", &T);
	getchar();

	for (i = 1; i <= T; i++) {
		for (j = 1; j <= 8; j++) {
			gear[i][j] = getchar() - '0';
			cout << gear[i][j] << " ";
		}	
		getchar();
		cout << endl;
	}

	scanf("%d", &K);
		
	for (l = 0; l < K; l++) {
		scanf("%d %d", &n_of_magnet, &d_of_magnet);
		for (j = 1; j <= T; j++) {
			save[j].first = 0;
			save[j].second = 0;
		}

		// 시계방향이면
		if (d_of_magnet == CW) {
			//왼쪽으로 propagete

			save[n_of_magnet].first = 1;
			save[n_of_magnet].second = CW;

			for (j = n_of_magnet; j > 1; j--) {
				if (save[j].first == 0) break;

				if (opposite(j, j - 1)) { // 반대라면
					save[j - 1].first = 1;
					save[j - 1].second = save[j].second * -1;
				}
				else {
					save[j - 1].first = 0;
				}
			}

			for (j = n_of_magnet; j < T; j++) {
				if (save[j].first == 0) break;

				if (opposite(j, j + 1)) {
					save[j + 1].first = 1;
					save[j + 1].second = save[j].second * -1;
				}
				else {
					save[j + 1].first = 0;
				}
			}
		}

		// 반시계방향이면

		else if (d_of_magnet == COUNTER_CW) {

			save[n_of_magnet].first = 1;
			save[n_of_magnet].second = COUNTER_CW;

			for (j = n_of_magnet; j > 1; j--) {
				if (save[j].first == 0) break;

				if (opposite(j, j - 1)) { // 반대라면
					save[j - 1].first = 1;
					save[j - 1].second = save[j].second * -1;
				}
				else {
					save[j - 1].first = 0;
				}
			}

			for (j = n_of_magnet; j < T; j++) {
				if (save[j].first == 0) break;

				if (opposite(j, j + 1)) {
					save[j + 1].first = 1;
					save[j + 1].second = save[j].second * -1;
				}
				else {
					save[j + 1].first = 0;
				}
			}
		}

		for (j = 1; j <= T; j++) {
			if (save[j].first == 1) {// 돌려야하는애
				turn_gear(j, save[j].second);
			}
		}
	}
		
	int score = 0;
	for (j = 1; j <= T; j++) {
		if (gear[j][1] == N) continue;
		score++;
	}

	printf("%d\n", score);
	return 0;
}


/* 톱니의 오른쪽이나 왼쪽과 맞닿아있는 곳을 조사해서 그 둘이 방향이 반대인지 체크한다. */
bool opposite(int n_of_gear, int p_of_gear) {
	if (n_of_gear < p_of_gear) { // p_of_gear는 오른쪽
		if (gear[n_of_gear][3] != gear[p_of_gear][7]) { // 방향이 반대라면
			return true;
		}

		return false;
	}
	else {	// p_of_gear는 왼쪽
		if (gear[n_of_gear][7] != gear[p_of_gear][3]) {	// 방향이 반대라면
			return true;
		}
		else {
			return false;
		}
	}
}

/* 회전 방향과  회전시키려는 톱니를 받아서 그대로 회전시킨다. */
void turn_gear(int n_of_gear, int turn_direction) {
	int temp, i;
	if (turn_direction == CW) { // 시계방향으로 돌려줘야함
		temp = gear[n_of_gear][8];
		for (i = 8; i > 1; i--) {
			gear[n_of_gear][i] = gear[n_of_gear][i - 1];
		}
		gear[n_of_gear][1] = temp;
	}
	else {	// 반시계방향으로 돌려줘야함
		temp = gear[n_of_gear][1];
		for (i = 1; i < 8 ; i++) {
			gear[n_of_gear][i] = gear[n_of_gear][i + 1];
		}
		gear[n_of_gear][8] = temp;
	}
}