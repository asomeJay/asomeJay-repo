/* Á÷°¢»ï°¢Çü */

#include <iostream>
#include <algorithm>
#include <ctgmath>

#define SWAP(a,b) {int t; t = a; a = b; b = t;}

using namespace std;

bool chk(int a, int b, int c);
int largest(int a, int b, int c);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int a, b, c;

	a = b = c = 1;
	while (1) {
		cin >> a >> b >> c;
		if (a == 0 && b == 0 && c == 0)
			break;
		if (chk(a, b, c)) {
			cout << "right" << '\n';
		}

		else {
			cout << "wrong" << '\n';
		}
	}
	return 0;
}

bool chk(int a, int b, int c) {
	int ta;
	ta = largest(a, b, c);
	if (ta == a) {
		return pow(a, 2) == pow(b, 2) + pow(c, 2);
	}
	else if (ta == b) {
		return pow(a, 2) + pow(c, 2) == pow(b, 2);
	}
	else {
		return pow(a, 2) + pow(b, 2) == pow(c, 2);
	}
}

int largest(int a, int b, int c) {
	return max(a, max(b, c));
}