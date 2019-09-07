#include <iostream>

using namespace std;

int main(void) {
	int a, b, n, w;
	int count = 0;
	int sheep = 0, goat = 0;
	cin >> a >> b >> n >> w;

	for (int i = 1, j = n - 1; i < n; i++, j--) {
		if (i * a + j * b == w) {
			count++;
			sheep = i;
			goat = j;
		}
	}

	if (count == 1) {
		cout << sheep << " " << goat;
		return 0;
	}

	cout << -1;
	return 0;
}
