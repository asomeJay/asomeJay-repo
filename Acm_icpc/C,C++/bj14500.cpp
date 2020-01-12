/* 砺闘稽耕葛 */

#include <iostream>
#include <algorithm>

using namespace std;

int ver1(int r, int c);
int ver2(int r, int c);
int ver3(int r, int c);
int ver3_2(int r, int c);
int ver4(int r, int c);
int ver5(int r, int c);
int maximum(int, int);


int grid_paper[501][501];
int N, M;

int main(void) {
	int i, j, sum, temp;
	scanf("%d %d", &N, &M);
	sum = 0;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++) 
			scanf("%d", &grid_paper[i][j]);
	}

	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++) {
			temp = maximum(i, j);
			if (sum < temp) {
				sum = temp;
			}
		}
	}

	printf("%d\n", sum);
	return 0;
}

// けけけけ
int ver1(int r, int c) {
	int i, sum, candi;
	sum = 0; candi = 0;
	if (c + 3 <= M) {
		for (i = 0; i < 4; i++) {
			sum += grid_paper[r][c + i];
		}
	}
	
	if (r + 3 <= N) {
		for (i = 0; i < 4; i++) {
			candi += grid_paper[r + i][c];
		}
	}
	return sum > candi ? sum : candi;
}

// けけ
// けけ
int ver2(int r, int c) {
	if (r + 1 > N) return 0;
	if (c + 1 > M) return 0;
	int i, j, sum;

	sum = 0;

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			sum += grid_paper[r + i][c + j];
		}
	}
	return sum;
}

//け
//け
//けけ
int ver3(int r, int c) {
	int i, sum, candi;
	sum = 0; candi = 0;
	if (r + 2 <= N && c + 1 <= M) {
		for (i = 0; i < 3; i++) {
			sum += grid_paper[r + i][c];
		}
		sum += grid_paper[r + 2][c + 1];
	}
	
	//けけけ
	//け
	if (r + 1 <= N && c + 2 <= M) {
		for (i = 0; i < 3; i++) 
			candi += grid_paper[r][c + i];
		
		candi += grid_paper[r + 1][c];
		sum = (sum > candi ? sum : candi);
		candi = 0;
	}
	
	//けけ
	//  け
	//  け
	if (r + 2 <= N && c + 1 <= M) {
		for (i = 0; i < 3; i++) 
			candi += grid_paper[r + i][c + 1];
		
		candi += grid_paper[r][c];
		sum = (sum > candi ? sum : candi);
		candi = 0;
	}
	
	//     け
	// けけけ
	if (r + 1 <= N && c + 2 <= M) {
		for (i = 0; i < 3; i++) 
			candi += grid_paper[r + 1][c + i];
	
		candi += grid_paper[r][c + 2];
		sum = (sum > candi ? sum : candi);
		candi = 0;
	}
	
	return sum;
}

//  け
//  け
//けけ
int ver3_2(int r, int c) {
	int i, sum, candi;
	sum = 0; candi = 0;

	if (r + 2 <= N && c + 1 <= M) {
		for (i = 0; i < 3; i++) {
			sum += grid_paper[r + i][c + 1];
		}
		sum += grid_paper[r + 2][c];
	}
	
	//け
	//けけけ
	if (r + 1 <= N && c + 2 <= M) {
		for (i = 0; i < 3; i++) {
			candi += grid_paper[r + 1][c + i];
		}	
		candi += grid_paper[r][c];

		sum = (sum > candi ? sum : candi);
		candi = 0;
	}
	
	//けけ
	//け
	//け
	if (r + 2 <= N && c + 1 <= M) {
		for (i = 0; i < 3; i++) {
			candi += grid_paper[r + i][c];
		}
		candi += grid_paper[r][c + 1];
		sum = (sum > candi ? sum : candi);
		candi = 0;
	}
	

	// けけけ
	//     け
	if (r + 1 <= N && c + 2 <= M) {
		for (i = 0; i < 3; i++) {
			candi += grid_paper[r][c + i];
		}
		candi += grid_paper[r + 1][c + 2];

		sum = (sum > candi ? sum : candi);
	}
	
	return sum;
}

//け
//けけ
//  け
int ver4(int r, int c) {
	int sum, candi;
	sum = 0; candi = 0;

	//  けけ
	//けけ
	if (r + 1 <= N && c + 2 <= M) {
		sum += grid_paper[r+1][c] + grid_paper[r][c + 1] + grid_paper[r + 1][c + 1] +
			grid_paper[r][c + 2];
	}

	//け
	//けけ
	//  け
	if (r + 2 <= N && c + 1 <= M) {
		candi += grid_paper[r][c] + grid_paper[r + 1][c] + grid_paper[r + 1][c + 1] +
			grid_paper[r + 2][c + 1];
	}
	sum = (sum > candi ? sum : candi);
	candi = 0;

	//  け
	//けけ
	//け
	if (r + 2 <= N && c + 1 <= M) {
		candi += grid_paper[r+2][c] + grid_paper[r + 1][c] + grid_paper[r + 1][c + 1] +
			grid_paper[r][c + 1];
	}
	sum = (sum > candi ? sum : candi);
	candi = 0;
	//けけ
	//  けけ
	if (r + 1 <= N && c + 2 <= M) {
		candi += grid_paper[r][c] + grid_paper[r + 1][c + 2] + grid_paper[r + 1][c + 1] +
			grid_paper[r][c + 1];
	}

	sum = (sum > candi ? sum : candi);
	return sum;
}

//けけけ
//  け
int ver5(int r, int c) {
	int i, sum, candi;
	sum = 0; candi = 0;

	//けけけ
	//  け
	if (r + 1 <= N && c + 2 <= M) {
		for (i = 0; i < 3; i++) {
			sum += grid_paper[r][c + i];
		}
		sum += grid_paper[r + 1][c + 1];
	}

	sum = (sum > candi ? sum : candi);
	candi = 0;
	//  け
	//けけ
	//  け
	
	if (r + 2 <= N && c + 1 <= M) {
		for (i = 0; i < 3; i++) {
			candi += grid_paper[r + i][c + 1];
		}
		candi += grid_paper[r + 1][c];
	}
	sum = (sum > candi ? sum : candi);
	candi = 0;

	//  け
	//けけけ
	if (r + 1 <= N && c + 2 <= M) {
		for (i = 0; i < 3; i++) {
			candi += grid_paper[r + 1][c + i];
		}
		candi += grid_paper[r][c + 1];
	}

	sum = (sum > candi ? sum : candi);
	candi = 0;

	//け
	//けけ
	//け
	if (r + 2 <= N && c + 1 <= M) {
		for (i = 0; i < 3; i++) {
			candi += grid_paper[r + i][c];
		}
		candi += grid_paper[r + 1][c + 1];
	}
	sum = (sum > candi ? sum : candi);
	candi = 0;
	return sum;
}

int maximum(int r, int c){
	int a, b, cc, d, e, ccc;
	a = ver1(r, c);
	b = ver2(r, c);
	cc = ver3(r, c);
	ccc = ver3_2(r, c);
	d = ver4(r, c);
	e = ver5(r, c);
	return max(ccc, max(a, max(b, max(cc, (max(d, e))))));
}