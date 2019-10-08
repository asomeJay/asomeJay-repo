#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>

using namespace std;

int oneDPower2(int *, int);	// 수업시간에 배웠던 1-dimension 최고합 구하는 식 복잡도가 N^2
int oneDPower1(int *, int);	// 수업시간에 배웠던 1-dimension 최고합 구하는 알고리즘, 복잡도가 N
int power6(int**, int, int);	// n^6으로 구현
int power4(int **, int, int);	// n^4로 구현
int power3(int **, int, int);	// n^3으로 구현

int main(int argc, char *argv[]) {
	string ma = argv[1];	// input 파일이 무엇인지 받아달라
	string ing = "result_" + ma; // output 파일 이름을 설정한다.
	clock_t start, end;	// 수행시간을 측정하기 위한 변수들
	double result;		// 수행시간 결과를 저장할 변수
	int algo_style, row, col, i, j, maxSum;	
	int** table;		// 2D metrix를 수행할 표
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
		
	case 1: // 복잡도가 n6
		maxSum = power6(table, row, col);
		break;
	case 2: // 복잡도가 n4
		maxSum = power4(table, row, col);
		break;
	case 3: // 복잡도가 n3
		maxSum = power3(table, row, col);
		break;
	default:	// 그 외 경우는 에러로 처리한다.
		cout << "Error breaks Out!" << endl;
		
	}
	end = clock();
	result = (double)(end-start);	// 수행시간을 result 변수에 저장한다.
	ofstream of(ing.c_str());	// output 파일을 저장하기 위한 작업
	if(!of.is_open()){
		cout << "Error breaks out at in.open()" << endl;
		exit(1);
	}
	
	of << argv[1] << endl << algo_style << endl << row << endl << col << endl << maxSum << endl << result << endl; // output 파일에 내가 원하는 정보를 저장한다. 
	
	return 0;
}


int oneDPower1(int *array, int num){ 	// 이 알고리즘은 수업에 배웠던 그대로이다.
	int maxSum = -2147483648, justSum = 0; // 합을 저장할 변수들 maxSum 은 음수를 처리하려고 최대한 작은 수를 설정했다.
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

int oneDPower2(int *array, int num){ // 이 알고리즘은 수업시간 때 배웠던 그대로이다. 
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
//for문 여섯 개를 이용해서 max sum subrectanble을 구한다. 직사각형의 양 끝점을 잡고 그 끝점을 순회하면서 각 칸에 있는 수를 더한다. 
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

	// cout << maxSum << "power6" << endl;
	return maxSum;
}

int power4(int ** table, int row, int col) {
//복잡도 O(N^4) 알고리즘.  
	int* oneDCol = (int *)malloc(sizeof(int) * col);
	int maxSum = -2147483648, justSum = 0; // 모든 수가 음수일 것을 대비해서 maxSum에 최저값을 설정한다.
	int i, j;

	for(int k = 0; k < row; k++){
		for(i = 0; i < col; i++)
			oneDCol[i] = 0; 	// one-dimension column을 0으로 초기화한다.

		for(i = k; i < row; i++){
			for(j = 0; j < col; j++){
				oneDCol[j] += table[i][j]; //여기에 table의 원소를 더해서 1-dimension을 만든다.
			}
		
			justSum = oneDPower2(oneDCol, col); // 만든 array에 수업시간에 배웠던 알고리즘을 적용한다.
			if(maxSum < justSum){		// maxSum과 justSum을 비교해서 justSum이 더 크면 maxSum을 바꾼다.
				maxSum = justSum;
			}
		}
	}
	// cout << maxSum << "power4" <<endl;
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
				oneDCol[j] += table[i][j]; // oneDCol을 초기화한다. 
			
			justSum = oneDPower1(oneDCol, col); // 만든 array에 수업시간에 배웠던 O(N) 알고리즘을 적용한다.
			if(maxSum < justSum)
				maxSum = justSum;
			
		}
	}
	// cout << maxSum << "power3" << endl;
	return maxSum;
}
