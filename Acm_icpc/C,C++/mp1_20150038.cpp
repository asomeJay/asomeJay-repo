#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>

using namespace std;

int oneDPower2(int *, int);
int oneDPower1(int *, int);
int power6(int**, int, int);	// n^6으로 구현
int power4(int **, int, int);	// n^4로 구현
int power3(int **, int, int);	// n^3으로 구현

int main(int argc, char *argv[]) {
	string ma = argv[1];
	string ing = "result_" + ma;
	clock_t start, end;
	double result;
	int algo_style, row, col, i, j, maxSum;
	int** table;
	ifstream in(argv[1]); // input으로 들어온 문서를 open 한다.
	if (!in.is_open()){	// Open()에 대해 Error Check
		cout << "Error breaks out at in.open()" << endl;
		exit(1);
	}
		
	algo_style = (int)(*argv[2] - '0'); // 어느 시간복잡도 함수를 실행할지 결정한다.
	in >> row >> col;		// 파일에서 row 값과 col 값을 읽음
	table = (int**)malloc(sizeof(int*) * row);	// input을 저장할 2d 배열 선언
	for (i = 0; i < row; i++)			// table의 각 행마다 열을 선언
		table[i] = (int *)malloc(sizeof(int) * col);
	
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++) // 만든 테이블에 input 값을 잘 넣어준다.
			in >> table[i][j];
	start = clock();
	switch (algo_style) {	// 어느 시간 복잡도로 할 것인가.
		
	case 1: // n6
		maxSum = power6(table, row, col);
		break;
	case 2: // n4
		maxSum = power4(table, row, col);
		break;
	case 3: // n3
		maxSum = power3(table, row, col);
		break;
	default:
		cout << "Error breaks Out!" << endl;
		
	}
	end = clock();
	result = (double)(end-start);
	ofstream of(ing.c_str());
	if(!of.is_open()){
		cout << "Error breaks out at in.open()" << endl;
		exit(1);
	}
	
	of << argv[1] << endl << algo_style << endl << row << endl << col << endl << maxSum << endl << result << endl;
	
	return 0;
}


int oneDPower1(int *array, int num){
	int maxSum = -2147483648, justSum = 0;
	int i;
	for(i = 0; i < num; i++){
		justSum += array[i];
		if (justSum > maxSum){
			maxSum = justSum;
		}
		if(justSum < 0){
			justSum = 0;
		}
	}
	
	return maxSum;
}

int oneDPower2(int *array, int num){
	int maxSum = -2147483648, justSum = 0;
	int i, j;
	for (i = 0; i < num; i++){

		justSum = 0;

		for (j = i; j < num; j++){
			justSum += array[j];
			if(justSum > maxSum){
				maxSum = justSum;
			}
		}
	}
	
	return maxSum;
}

int power6(int **table, int row, int col) {
//for문 여섯 개를 이용해서 max sum subrectanble을 구한다.
	int maxSum = -2147483648, justSum = 0;
	int ix,iy, jx,jy, kx,ky;
	for(ix = 0; ix < row; ix++){
		for(iy= 0; iy < col; iy++){

			for(jx = ix; jx < row; jx++){
				for(jy = iy; jy < col; jy++){
					justSum = 0;
					for(kx = ix; kx <= jx; kx++){
						for(ky = iy; ky <= jy; ky++){
							justSum += table[kx][ky];
						}
					}
					if (maxSum < justSum)
						maxSum = justSum;
					
				} 
			}
		}
	}

	cout << maxSum << "power6" << endl;
	return maxSum;
}
int power4(int ** table, int row, int col) {
	int* oneDCol = (int *)malloc(sizeof(int) * col);
	int maxSum = -2147483648, justSum = 0;
	int i, j;

	for(int k = 0; k < row; k++){
		for(i = 0; i < col; i++)
			oneDCol[i] = 0;

		for(i = k; i < row; i++){
			for(j = 0; j < col; j++){
				oneDCol[j] += table[i][j];
			}
		
			justSum = oneDPower2(oneDCol, col);
			if(maxSum < justSum){
				maxSum = justSum;
			}
		}
	}
	cout << maxSum << "power4" <<endl;
	return maxSum;
}
int power3(int ** table, int row, int col) {
	int* oneDCol = (int *)malloc(sizeof(int) * col);
	int maxSum = -2147483648, justSum = 0;
	int i, j;

	for(int k = 0; k < row; k++){
		for(i = 0; i < col; i++)
			oneDCol[i] = 0;
		
		for(i = k; i < row; i++){
			for(j = 0; j < col; j++)
				oneDCol[j] += table[i][j];
			
			justSum = oneDPower1(oneDCol, col);
			if(maxSum < justSum)
				maxSum = justSum;
			
		}
	}
	cout << maxSum << "power3" << endl;
	return maxSum;
}
