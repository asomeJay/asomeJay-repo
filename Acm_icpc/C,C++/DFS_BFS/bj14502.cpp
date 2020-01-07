/* ¿¬±¸¼Ò */

#include <iostream>
#include <array>
#include <stack>

using namespace std;

void lab_search(int[9][9], int f_r, int f_c, int s_r, int s_c, int t_r, int t_c, int);
int dfs(int [9][9], int);

int s_of_safe;
int N, M;

array<pair<int, int>, 11> virus;
array<pair<int, int>, 81> zero_zone;

int z_index, v_index;
int z_count;

int main(void){
	int lab[9][9], i, j, k;

	scanf("%d %d", &N, &M);

	z_index = 1;
	v_index = 1;

	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++) {
			scanf("%d", &lab[i][j]);

			if (lab[i][j] == 0) 
				zero_zone[z_index++] = make_pair(i, j);	// ºó Ä­ À§Ä¡

			else if (lab[i][j] == 2) 
				virus[v_index++] = make_pair(i, j);	// Virus À§Ä¡
		}
	}

	for (i = 1; i < z_index; i++) {
		for (j = i + 1; j < z_index; j++) {
			for (k = j + 1; k < z_index; k++) {
				lab_search(lab, zero_zone[i].first, zero_zone[i].second, zero_zone[j].first, zero_zone[j]
					.second, zero_zone[k].first, zero_zone[k].second, z_index-1);
			}
		}
	}

	printf("%d\n", z_count);

	return 0;
}

void lab_search(int lab_[9][9], int f_r, int f_c, int s_r, int s_c, int t_r, int t_c, int zero_count){
	int lab[9][9], temp;

	copy(&lab_[0][0], &lab_[0][0] + 9 * 9, &lab[0][0]);

	lab[f_r][f_c] = 1;
	lab[s_r][s_c] = 1;
	lab[t_r][t_c] = 1;

	temp = dfs(lab, zero_count-3);

	if (z_count < temp) {
		z_count = temp;
		/*
		int i, j, k;
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= M; j++) {
				printf("%d ", lab[i][j]);
			}
			printf("\n");
		}*/
	}

	lab[f_r][f_c] = 0;
	lab[s_r][s_c] = 0;
	lab[t_r][t_c] = 0;

	return;
}

int dfs(int lab[9][9], int zero) {
	int i, j, k;
	int n_r, n_c;

	stack<pair<int, int>> s;

	for (i = 1; i < v_index; i++) {
		s.push(make_pair(virus[i].first, virus[i].second));

		while (!s.empty()) {
			n_r = s.top().first;
			n_c = s.top().second;

			s.pop();

			if ((n_r + 1 <= N) && lab[n_r + 1][n_c] == 0) {
				lab[n_r + 1][n_c] = 2;
				s.push(make_pair(n_r + 1, n_c));

				zero--;
			}

			if (n_r - 1 >= 1 && lab[n_r - 1][n_c] == 0 ) {
				lab[n_r - 1][n_c] = 2;
				s.push(make_pair(n_r - 1, n_c));

				zero--;
			}

			if ((n_c + 1 <= M) && lab[n_r][n_c + 1] == 0) {
				lab[n_r][n_c + 1] = 2;
				s.push(make_pair(n_r, n_c + 1));

				zero--;
			}

			if (n_c - 1 >= 1 && lab[n_r][n_c - 1] == 0) {
				lab[n_r][n_c - 1] = 2;
				s.push(make_pair(n_r, n_c - 1));

				zero--;
			}
		}
	}
	return zero;
}