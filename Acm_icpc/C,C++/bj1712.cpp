#include <iostream>
#include <cstdlib>
#include <tgmath.h>

using namespace std;

int main(void) {
	long double A, B, C;
	long long int n;
	//cin >> A >> B >> C;
	scanf("%llf", &A); scanf("%llf", &B); scanf("%llf", &C);

	if (B >= C) {
		printf("-1");
		return 0;
	}
	
	n = floor(A / (C - B));
	printf("%lld\n", n + 1);

	return 0;
}