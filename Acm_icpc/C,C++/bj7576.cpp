/* bj7576 : 토마토 */

#include <iostream>

using namespace std;

int zero, day;

void spread(int**, int row_, int col_, int, int);
void copy_t(int**, int**, int, int);

int main(void) {
	int save_zero, col, row, i, j, k, temp; scanf("%d %d", &col, &row); // M은 가로, N은 세로
	zero = 0; save_zero = -1;

	int** table = new int*[row];
	int** copy_table = new int* [row];

	for (i = 0; i < row; i++) {
		table[i] = new int[col];
		copy_table[i] = new int[col];
	}
		
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			scanf("%d", &temp);
			table[i][j] = temp;
			if (temp == 0) zero++; // 박스에서 0인 공간의 개수 
		}
	}

	/* 모든 토마토가 익어있는 상태 */
	if (zero == 0) {
		printf("0\n");
		return 0;
	}

	copy_t(table, copy_table, row, col);

	while(1){
	for (i = 0; i < row; i++) {	
		for (j = 0; j < col; j++) {
			if (table[i][j] == 1) {
				spread(copy_table, i, j, row, col);
			}
		}
	  }

	copy_t(copy_table, table, row, col);
	day++;

	if (zero == 0)break;

	if (save_zero == zero) {
		day = -1;
		break;
	}
	save_zero = zero;
	}
	printf("%d\n", day);
	return 0;
}

//void spread(int ** table, int row_, int col_, int row_lim, int col_lim) {
void spread(int** table, int row_, int col_, int row_lim, int col_lim) {
	int row, col; row = row_; col = col_;
	int row_limit = row_lim, col_limit; col_limit = col_lim;

	//table[row][col] = 1;

	// 아래에 있는 것
	if ((row < row_limit-1) && table[row + 1][col] == 0) {
		table[row + 1][col] = 2;
		zero--;
	}

	// 위에 있는 것
	if ((row > 0) && table[row - 1][col] == 0) {
		table[row - 1][col] = 2;
		zero--;
	}

	// 왼쪽에 있는 것
	if ((col > 0) && table[row][col - 1] == 0) {
		zero--;
		table[row][col - 1] = 2;
	}
		
	// 오른쪽에 있는 것
	if ((col < col_limit-1) && table[row][col + 1] == 0) {
		table[row][col + 1] = 2;
		zero--;
	}
	//spread(table, row, col + 1, row_limit, col_limit);
}

void copy_t(int** origin, int** target, int i_lim, int j_lim) {
	int i, j;
	for (i = 0; i < i_lim; i++) {
		for (j = 0; j < j_lim; j++) {
			if (origin[i][j] == 2) origin[i][j] = 1;
			target[i][j] = origin[i][j];
		}
	}
}