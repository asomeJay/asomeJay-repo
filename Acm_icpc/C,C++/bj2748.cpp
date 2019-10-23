#include <iostream>

using namespace std;

int main(void) {
	int n;
	cin >> n;
	long int* container = (long int*)malloc(sizeof(long int) * (n + 1));
	container[0] = 0;
	container[1] = 1;
	for (int i = 2; i <= n; i++) {
		container[i] = container[i - 1] + container[i - 2];
	}
	cout << container[n];

	return 0;
}