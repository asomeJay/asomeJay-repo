#include <iostream>

using namespace std;

int main(void) {
	int max = 0, index;
	int i, num;

	for (i = 0; i < 9; i++) {
		cin >> num;
		if (max < num) {
			index = i + 1;
			max = num;
		}
	}

	cout << max << endl << index << endl;

	return 0;
}