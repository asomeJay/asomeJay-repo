/* ATM */

#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;

int main(void) {
	int i, j, k, n; cin >> n;
	vector<long long int> table(n + 1);
	table[0] = 0;
	for (i = 1; i <= n; i++) {
		cin >> table[i];
	}
	sort(table.begin(), table.end());
	long long int result = table[1];
	for (i = 2; i <= n; i++) {
		table[i] += table[i - 1];
		result += table[i];
	}
		
	cout << result << endl;
	return 0;
}