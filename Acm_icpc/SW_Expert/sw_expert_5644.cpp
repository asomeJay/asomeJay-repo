/* 무선 충전 */

#include <iostream>
#include <algorithm>

#define MAX_MOVE 100 + 2
#define MAX_BC_NUM 8 + 1
#define MAX_BC_RANGE 4 + 1
#define MAX_BC_POWER 500 + 1
#define OVERLAP 1

class ac_point {
public:
	int r, c;
	int range, power;
};

using namespace std;

int dist(int a, int b, int c, int d);
int another(int r, int c, int);
void init();

int dr[5] = { 0, -1, 0, 1, 0 };
int dc[5] = { 0, 0, 1, 0, -1 };
int A[MAX_MOVE], B[MAX_MOVE];
int n_of_move, n_of_ac, ar, ac, br, bc, a_sum, b_sum;
ac_point acp[MAX_BC_NUM];

int main(void) {
	int i, j, k, t_of_case;
	int ta_sum, tb_sum, ac_range, another_a, another_b, a_ind, b_ind, a_dist, b_dist;

	cin >> t_of_case;
	
	for (i = 1; i <= t_of_case; i++) {
		init();
		cin >> n_of_move >> n_of_ac;
		for (j = 1; j <= n_of_move; j++)
			cin >> A[j];
		for (j = 1; j <= n_of_move; j++)
			cin >> B[j];

		for (j = 1; j <= n_of_ac; j++) {
			cin >> acp[j].c >> acp[j].r;
			cin >> acp[j].range >> acp[j].power;
		}

		for (j = 0; j <= n_of_move; j++) {
			ar += dr[A[j]]; ac += dc[A[j]];
			br += dr[B[j]]; bc += dc[B[j]];

			ta_sum = tb_sum = 0;
			a_ind = -1; b_ind = -2;

			/* a와 b의 현재 자리에서 얻을 수 있는 가장 큰 BC를 찾습니다. */
			for (k = 1; k <= n_of_ac; k++) {
				ac_range = acp[k].range; 
				a_dist = dist(acp[k].r, acp[k].c, ar, ac); 
				b_dist = dist(acp[k].r, acp[k].c, br, bc); 

				if (a_dist <= ac_range) {
					if (ta_sum < acp[k].power) {
						ta_sum = acp[k].power;
						a_ind = k;
					}
				}
				if (b_dist <= ac_range) {
					if (tb_sum < acp[k].power) {
						tb_sum = acp[k].power;
						b_ind = k;
					}
				}
			}

			// a와 b가 현재 자리에서 얻을 수 있는 가장 큰 BC가 동일하다면 
			// 그에 걸맞는 처리를 해줍니다. 
			if (a_ind == b_ind) {
				k = a_ind;
				another_a = another(ar, ac, k);
				another_b = another(br, bc, k);

				//둘다 중복되는 게 없다.
				if (another_a == -1 && another_b == -1) {
					ta_sum = tb_sum = acp[k].power / 2;
				}
				//a는 중복X b는 중복 O. 
				else if (another_a == -1 && another_b != -1) {
					ta_sum = acp[k].power;
					tb_sum = acp[another_b].power;
				}

				//a는 중복되는 게 있는데 b는 중복되는 게 없다. 
				else if (another_a != -1 && another_b == -1) {
					tb_sum = acp[k].power;
					ta_sum = acp[another_a].power;
				}
				//a는 중복X B도 중복 X
				else if (another_a != -1 && another_b != -1) {
					
					if (acp[another_a].power < acp[another_b].power) {
						tb_sum = acp[another_b].power;
						ta_sum = acp[k].power;
					}
					else {
						tb_sum = acp[k].power;
						ta_sum = acp[another_a].power;
					}
				}
			}
			a_sum += ta_sum;
			b_sum += tb_sum;
		}

		cout << "#" << i << " " << a_sum + b_sum << '\n';
	}

	return 0;
}

int dist(int a, int b, int c, int d) {
	return abs(c - a) + abs(d - b);
}

void init() {
	fill(A, A + MAX_MOVE, 0);
	fill(B, B + MAX_MOVE, 0);

	for (int i = 1; i <= n_of_ac; i++) {
		acp[i].r = acp[i].c = 0;
		acp[i].power = acp[i].range = 0;
	}

	n_of_move = n_of_ac = 0;
	a_sum = b_sum = 0;
	ar = ac = 1; br = bc = 10;

}

int another(int r, int c, int ind) {
	int i, dista, maxi, max_ind;
	maxi = -1, max_ind = -1;
	for (i = 1; i <= n_of_ac; i++) {
		dista = dist(r, c, acp[i].r, acp[i].c);
		if (i != ind && dista <= acp[i].range) {
			if (maxi < acp[i].power) {
				maxi = acp[i].power;
				max_ind = i;
			}
		}
	}
	return max_ind;
}