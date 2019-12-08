#include <iostream>

using namespace std;

int table[1000001];

int main(void) {
	int i, j, k, n; cin >> n;
	int temp, tt;
	for (i = 1; i <= n; i++) {
		tt = i;
		temp = i;
		while (tt > 0) {
			temp += tt % 10;
			tt /= 10;
		}
		if(table[temp] == 0)
			table[temp] = i;
	}

	cout << table[n] << endl;
	return 0;
}