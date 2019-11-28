/* Subsequence Sum */
#include <iostream>

#define INT_MA 2147483647

using namespace std;

int table[100001];

int main(void) {
	int i, j, k, n, sum, max_sum, flag, small; cin >> n;
	for (i = 1; i <= n; i++) {
		cin >> table[i];
	}
	sum = 0; max_sum = 0; flag = 1; small = -1 * INT_MA;

	for (i = 1; i <= n; i++) {
		if (table[i] >= 0)
			flag = 0;

		if (table[i] < 0 && small < table[i])
			small = table[i];

		sum += table[i];

		if (sum < 0)
			sum = 0;
		if (sum > max_sum)
			max_sum = sum;
	}


	if (flag == 1)
		cout << small << endl;
	else {
		cout << max_sum << endl;
	}
	
	return 0;
}