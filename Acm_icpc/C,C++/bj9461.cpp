#include <iostream>

using namespace std;

int main(void) {
	int n,i, j, t; cin >> t ;

	long long int* arr = (long long int*)malloc(sizeof(long long int) * 150);

	arr[0] = arr[1] = arr[2] = 1;
	arr[3] = 2; arr[4] = 2; arr[5] = 3;

	for (i = 6; i < 150; i++) {
		arr[i] = arr[i - 1] + arr[i - 5];
	}

	for (j = 0; j < t; j++) {
		cin >> n;
		printf("%lld\n", arr[n-1]);
	}
	

	

	return 0;
}