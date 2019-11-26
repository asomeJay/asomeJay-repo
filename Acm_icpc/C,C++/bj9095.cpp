#include <iostream>

using namespace std;

int one_two_thr(int target_number, int num_count, int num_size, int result);
int nCr(int n, int r);
long long int factorial(int n);

int main(void) {
	
	int n, i, j, count, sum, target_num, result, row = 12;
	
	scanf("%d", &n);
	int table[12] = { 0 };
	table[0] = 0;
	table[1] = 1;
	table[2] = 2;
	table[3] = 4;

	for (i = 4; i < row; i++) {
		table[i] = table[i - 3] + table[i - 2] + table[i - 1];
	}
	for (i = 0; i < n; i++) {

		result = 0;
		cin >> target_num;
		

		cout << "result : " << table[target_num] << endl;
	}

	return 0;
}

int one_two_thr(int target_number, int num_count, int num_size, int result) {
	if (target_number < num_size) return 0;
	int left_num = target_number - num_size;
	result += nCr(left_num, num_count);
	result += one_two_thr(target_number, num_count + 1, num_size + 2, result);
	result += one_two_thr(target_number, num_count + 1, num_size + 3, result);
	return result;
}

int nCr(int n, int r) {
	long int temp = (factorial(n) / (factorial(n - r) * factorial(r)));
	if (temp < 0) return -1;
	return temp;
}

long long int factorial(int n) {
	long long int i, result = 1;

	for (i = n; i > 0; i--) {
		result = result * n;
	}
	return result;
}