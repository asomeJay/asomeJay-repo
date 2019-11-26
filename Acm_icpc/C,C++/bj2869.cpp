#include <iostream>
#include <tgmath.h>

using namespace std;

int main(void) {
	long long int A, B, V;
	cin >> A >> B >> V;
	long int div;
	div = (V - A) / (A - B);
	if ((A - B) * div != (V - A)) {
		div += 2;
	}
	else {
		div++;
	}

	printf("%ld\n", div);

	return 0;
}