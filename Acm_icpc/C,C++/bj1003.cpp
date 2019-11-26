#include <iostream>

using namespace std;

typedef struct zero_one {
	int zero;
	int one;
}num_count;


num_count counter[50];

void fib(int n);

int main(void) {
	int n, i, t;
	cin >> t;

	counter[0].zero = 1;
	counter[0].one = 0;

	counter[1].zero = 0;
	counter[1].one = 1;

	for (i = 2; i < 50; i++) {
		counter[i].zero = counter[i - 2].zero + counter[i - 1].zero;
		counter[i].one = counter[i - 2].one + counter[i - 1].one;
	}
	for (i = 0; i < t; i++) {
		cin >> n;

		cout << counter[n].zero << " " << counter[n].one << endl;
	}
	return 0;
}