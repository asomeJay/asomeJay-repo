/* 활주로 */

#include <iostream>
#include <algorithm>

#define MAX_LAND 22
#define OUT_OF_RANGE 0
#define IN_RANGE 1
#define CANT 0
#define CAN 1

using namespace std;

/* Input : NONE 
   Output : NONE
   n_of_airstrip 등 변수를 초기화한다. */
void init();
bool chk_horizontal(int );
bool chk_vertical(int );
bool is_range(int r, int c);

int N, len_of_runway, n_of_airstrip; // airstrip은 활주로라는 의미다. 
int land[MAX_LAND][MAX_LAND];

int main(void) {
	int i, j, k, t_case;
	cin >> t_case;

	for (i = 1; i <= t_case; i++) {
		init();
		cin >> N >> len_of_runway;

		// LAND를 채우는 과정 
		for (j = 1; j <= N; j++) {
			for (k = 1; k <= N; k++) {
				cin >> land[j][k];
			}
		}
	;
		for (j = 1; j <= N; j++) {
			if (chk_horizontal(j) == CAN) {
		//		cout << "horizon : " << j << endl;
				n_of_airstrip++; 
			}
				
			if (chk_vertical(j) == CAN) {
		//		cout << "Vertical : " << j << endl;
				n_of_airstrip++;
			}
				
		}

		cout << "#" << i << " " << n_of_airstrip << '\n';
	}

	return 0;
}

void init() {
	n_of_airstrip = 0;
	fill(&land[0][0], &land[MAX_LAND - 1][MAX_LAND], 0);
}

bool chk_horizontal(int row) {
	bool is_visit[MAX_LAND] = { 0 };
	int i, j, k, tmp, t_val;
	for (i = 1; i <= N-1; i++) {
		if (abs(land[row][i+1] - land[row][i]) > 1)
			return CANT;

		if (land[row][i] < land[row][i + 1]) {
			for (k = 0; k <= len_of_runway - 1; k++) {
				tmp = i - k;
				if (is_visit[tmp] == true)
					return CANT;

				if (is_range(row, tmp) == OUT_OF_RANGE) 
					return CANT;

				if (k < len_of_runway - 1 && (tmp-1 <= 0 ||land[row][tmp] != land[row][tmp - 1]))
					return CANT;

				is_visit[tmp] = true;
			}
		}
		else if (land[row][i] > land[row][i + 1]){
			for (k = i+1; k <= i + len_of_runway; k++) {
				if (is_visit[k] == true)
					return CANT;

				if (is_range(row, k) == OUT_OF_RANGE)
					return CANT;

				if (k < len_of_runway + i && (k+1 > N || land[row][k] != land[row][k + 1]))
					return CANT;

				is_visit[k] = true;
			}
		}
	}

	return CAN;
}
bool chk_vertical(int col) {
	bool is_visit[MAX_LAND] = { 0 };
	int i, j, k, tmp, t_val;
	for (i = 1; i <= N - 1; i++) {
		if (abs(land[i + 1][col] - land[i][col]) > 1)
			return CANT;

		if (land[i][col] < land[i + 1][col]) {

			for (k = 0; k <= len_of_runway - 1; k++) {
				tmp = i - k;

				if (is_visit[tmp] == true)
					return CANT;

				if (is_range(col, tmp) == OUT_OF_RANGE)
					return CANT;

				if (k < len_of_runway - 1 && (tmp - 1 <= 0 || land[tmp][col] != land[tmp - 1][col]))
					return CANT;

				is_visit[tmp] = true;
			}
		}
		else if (land[i][col] > land[i + 1][col]) {
			for (k = i + 1; k <= len_of_runway + i; k++) {

				if (is_visit[k] == true)
					return CANT;

				if (is_range(col, k) == OUT_OF_RANGE)
					return CANT;

				if (k < len_of_runway + i && ((k+1 > N) || land[k][col] != land[k+1][col]))
					return CANT;

				is_visit[k] = true;
			}
		}
	}

	return CAN;
}

bool is_range(int r, int c) {
	return r >= 1 && r <= N && c >= 1 && c <= N;
}