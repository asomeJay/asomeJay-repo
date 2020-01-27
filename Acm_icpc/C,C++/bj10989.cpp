/* 수 정렬하기 3 */

#include <iostream>

using namespace std;

int arr[10001];

int main(void) {
	int N, i, temp;
	
	scanf("%d", &N);

	for (i = 0; i < N; i++) {
		scanf("%d", &temp);
		arr[temp]++;
	}
		
	for (i = 1; i <= 10000; i++) {
		for (int j = 0; j < arr[i]; j++) {
			printf("%d\n", i);
		}
	}
		
	
	return 0;
}