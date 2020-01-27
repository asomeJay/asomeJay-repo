/* °ËÁõ¼ö */

#include <iostream>
#include <tgmath.h>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int i, temp, total;
	total = 0;
	for (i = 1; i <= 5; i++) {
		cin >> temp;
		total += pow(temp, 2);
	}
	total %= 10;
	
	cout << total;

	return 0;
}