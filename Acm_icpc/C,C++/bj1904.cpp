#include <iostream>

#define LEN 1000005

using namespace std;


int main(void) {
	int* arr;
	int n, i; cin >> n;
	arr = (int*)malloc(sizeof(int) * LEN);
	arr[0] = arr[1] = 1; arr[2] = 2;
	for (i = 3; i < LEN; i++) {
		arr[i] = (arr[i - 1] + arr[i - 2]) % 15746;
	}

	printf("%d\n", arr[n]);

	return 0;
}