/* Generation of Tribbles */

#include <iostream>

using namespace std;

long long int fib[68];

int main(void) {
	int t, n; scanf("%d", &t);
	int i, j, k;

	fib[0] = fib[1] = 1;
	fib[2] = 2;
	fib[3] = 4;

	for (i = 4; i <= 67; i++) 
		fib[i] = fib[i - 1] + fib[i - 2] + fib[i - 3] + fib[i - 4];

	for (i = 1; i <= t; i++) {
		scanf("%d", &n);
		printf("%lld\n", fib[n]);
	}



	return 0;
}