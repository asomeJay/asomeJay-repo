#include <iostream>
#include <cmath>

using namespace std;
//
int main(void) {
	long long int input, lowerLimit, upperLimit;
	int n = 1;
	
	cin >> input;
	while (1) {
		lowerLimit = n * pow(2, n) - 1;
		upperLimit = (n + 1) * pow(2, (n+1)) - 1;
		if (input > lowerLimit && input <= upperLimit) {
			break;
		} 
		n++;
	}

	cout << n;

	return 0;
}
