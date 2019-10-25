#include <iostream>

using namespace std;

int main(void) {
	int findNum = 0, i;
	int inputPeople, inputGate;

	cin >> inputPeople >> inputGate;
	int getOut[101];
	bool check[101];

	for (i = 0; i < inputPeople; i++) {
		cin >> getOut[i];
		check[i] = false;
	}

	for (i = 0; i < inputGate; i++) {
		findNum = 0;
		for (int j = 0; j < inputPeople; j++) {
			if (check[j]) continue;

			if (findNum < getOut[j]) {
				check[j] = true;
				findNum = getOut[j];
			}
		}
	}

	for (i = 0; i < inputPeople; i++) {
		if (!check[i]) {
			cout << "NO";
			return 0;
		}
	}
	cout << "YES";
	return 0;
}
