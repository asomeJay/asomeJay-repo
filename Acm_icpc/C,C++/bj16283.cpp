#include <iostream>

using namespace std;

void same(int a, int b, int n, int w);

int main(void) {
	int a, b, n, w;
	int count = 0;
	int sheep = 0, goat = 0;
	cin >> a >> b >> n >> w;

	for (int i = 1, j = n - 1; i <= n; i++, j--) {
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

/*int main(void) {
	int a, b, n, w;
	double S = 0, G = 0;
	cin >> a >> b >> n >> w;

	same(a, b, n, w);	 //a == b인 케이스 체크

	S = n + ((a * n - w) / ((double)b - a));
	G = (w - a * n) / ((double)b - a);

	if ((S <= 0) || (G <= 0) ||
		(G - (int)G != 0) || (S - (int)S != 0)) {
		cout << -1;
		return 0;
	}

	cout << S << " " << G;
	return 0;
}

void same(int a, int b, int n, int w) {
	if (b - a == 0) {
		if (a + b == w) {
			cout << 1 << " " << 1;
			exit(0);
		}
		cout << -1;
		exit(0);
	}
}*/
