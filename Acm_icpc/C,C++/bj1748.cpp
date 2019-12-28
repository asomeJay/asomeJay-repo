/* 수 이어쓰기 */

#include <iostream>
#include <string>

using namespace std;

long long int ans; 
long long int d[10];

int main(void) {
	string n;
	long long int i, nn, digit; cin >> n;
	
	digit = n.size();
	nn = stoi(n);
	if (digit == 1) {
		printf("%d\n", stoi(n));
		return 0;
	}
	
	d[1] = 9;
	for (i = 2; i <= digit; i++) 
		d[i] = d[i - 1] + i * 9 * (long long int)pow(10, i - 1);

	printf("%lld\n", d[digit - 1] + (nn - (long long int)pow(10, digit - 1) + 1) * digit);

	return 0;
}