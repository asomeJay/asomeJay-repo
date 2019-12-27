/* °ö¼À */

#include <iostream>

using namespace std;

long long int r_fill(int, int );

long long int A, B, C;
int main(void) {
	long long int i;

	scanf("%lld %lld %lld", &A, &B, &C);

	i = r_fill(A, B) % C;

	printf("%lld\n", i);

	return 0;
}

long long int r_fill(long long int down, long long int up) {
	if (up == 0) return 1;
	if (up == 1) return down % C;
	
	if (up % 2 == 0) {
		return r_fill(down * down %C, up / 2) % C;
	}
	else {
		return down* r_fill(down * down % C, up / 2) % C;
	}
}