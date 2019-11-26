#include <iostream>

#define LENGTH 100

using namespace std;

int main(void) {
	int i, j, k, n;
	long long int* zero_arr, * one_arr;
	scanf("%d", &n);
	zero_arr = (long long int*)malloc(sizeof(long long int) * LENGTH);
	one_arr = (long long int*)malloc(sizeof(long long int) * LENGTH);

	zero_arr[0] = 0; one_arr[0] = 0;
	zero_arr[1] = 0; one_arr[1] = 1;
	zero_arr[2] = 1; one_arr[2] = 0;
	for (i = 3; i < LENGTH; i++) {
		zero_arr[i] =  (zero_arr[i - 1] + one_arr[i - 1]);
		one_arr[i] = zero_arr[i - 1];
	}

	printf("%lld\n", zero_arr[n] + one_arr[n]);

	return 0;
}
/*
void fib(int n) {
	long long int a, b, c, i;
	a = 1; b = 1;

	for (i = 2; i < n; i++) {
		c = a + b;
		a = b;
		b = c;
	}
	cout << c << endl;
}*/