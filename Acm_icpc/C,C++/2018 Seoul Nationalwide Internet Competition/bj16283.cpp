#include <iostream>
//
using namespace std;

void same(int a, int b, int n, int w);

int main(void) {
	int a, b, n, w;
	double S = 0, G = 0;
	cin >> a >> b >> n >> w;

	same(a, b, n, w);	 //a == bÀÎ ÄÉÀÌ½º Ã¼Å©

	double numerator = w - a * n;
	double denominator = b - a;

	S = n - (numerator / denominator);
	G = (numerator/ denominator);

	if ((S <= 0) || (G <= 0) ||
		(G - (int)G != 0) || (S - (int)S != 0)) {
		cout << -1;
		return 0;
	}

	cout << S << " " << G;
	return 0;
}

void same(int a, int b, int n, int w) {
	if ((b - a) == 0) {
		if ((a + b) == w && n == 2) {
			cout << 1 << " " << 1;
			exit(0);
		}
		cout << -1;
		exit(0);
	}
}
