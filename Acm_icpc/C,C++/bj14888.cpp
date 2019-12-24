/* 백트랙킹 : 연산자 끼워넣기 */

#include <iostream>
#include <algorithm>

#define PLU 1
#define MIN 2
#define MUL 3
#define DIV 4

using namespace std;


void back_plus(int , int);
void back_minus(int, int );
void back_multi(int, int );
void back_divide(int, int );

int number[20];
int pmmd[5];
int operate_pos[20];

long long int ans_max, ans_min, n;

int main(void) {
	int i, j, k;
	scanf("%d", &n);

	for (i = 1; i <= n; i++) {
		scanf("%d", &number[i]);
	}

	for (i = 1; i <= 4; i++) {
		scanf("%d", &pmmd[i]);
	}

	ans_max = -9999999999;
	ans_min = 9999999999;

	/* PLUS */
	if (pmmd[1] != 0) {
		for (i = 1; i <= n - 1; i++) {
			operate_pos[i] = PLU;
			back_plus(1, i);
			operate_pos[i] = 0;
		}
	}

	/* MINUS */
	else if (pmmd[2] != 0) {
		for (i = 1; i <= n - 1; i++) {
			operate_pos[i] = MIN;
			back_minus(1, i);
			operate_pos[i] = 0;
		}
	}

	/* MULTIPLEX */
	else if (pmmd[3] != 0) {
		for (i = 1; i <= n - 1; i++) {
			operate_pos[i] = MUL;
			back_multi(1, i);
			operate_pos[i] = 0;
		}
	}

	/* DIVIDE */
	else if (pmmd[4] != 0) {
		for (i = 1; i <= n - 1; i++) {
			operate_pos[i] = DIV;
			back_divide(1, i);
			operate_pos[i] = 0;
		}
	}

	printf("%lld\n%lld", ans_max, ans_min);
	return 0;
}

void back_plus(int depth, int index) {
	int i, j, k;

	/* plus를 다 배치했다. */
	if (depth >= pmmd[1]) {
		back_minus(0, 0);
	}

	/* Plus 아직 다 배치 못했다.*/
	else {
		for (i = index + 1; i <= n - 1; i++) {
			operate_pos[i] = PLU;
			back_plus(depth + 1, i);
			operate_pos[i] = 0;
		}
	}
}

void back_minus(int depth, int index) {
	int i, j, k;

	if (depth >= pmmd[2]) {
		back_multi(0, 0);
	}

	else {
		for (i = index + 1; i <= n - 1; i++) {
			if (operate_pos[i] == 0) {
				operate_pos[i] = MIN;
				back_minus(depth + 1, index);
				operate_pos[i] = 0;
			}
		}

	}
}

void back_multi(int depth, int index) {
	int i, j, k;

	if (depth >= pmmd[3]) {
		back_divide(0, 0);
	}

	else {
		for (i = index + 1; i <= n - 1; i++) {
			if (operate_pos[i] == 0) {
				operate_pos[i] = MUL;
				back_multi(depth + 1, i);
				operate_pos[i] = 0;
			}
		}
	}
}
void back_divide(int depth, int index) {
	int i, j, k;

	if (depth >= pmmd[4]) {
		long long int temp_sum = number[1];
		for (i = 1; i <= n-1; i++) {
	//		printf("operate pos : %d\n", operate_pos[i]);
			switch (operate_pos[i]) {
			case PLU :
//				printf("gg\n");
				temp_sum += number[i + 1];
				break;
			case MIN:
				temp_sum -= number[i + 1];
				break;
			case MUL:
				temp_sum *= number[i + 1];
				break;
			case DIV:
				temp_sum /= number[i + 1];
				break;
			default: 
				printf("ERROR BACK DIVIIDE\n");
				break;
			}
		}
		ans_max = max(ans_max, temp_sum);
		ans_min = min(ans_min, temp_sum);
	}

	else {
		for (i = index + 1; i <= n - 1; i++) {
			if (operate_pos[i] == 0) {
				operate_pos[i] = DIV;
				back_divide(depth + 1, i);
				operate_pos[i] = 0;
			}
		}
	}
}