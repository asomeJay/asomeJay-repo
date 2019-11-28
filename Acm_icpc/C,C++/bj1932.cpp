#include <iostream>
#include <algorithm>

using namespace std;

long long int power(int n);
long long int tri_table[500][500] = { 0 };

int main(void) {
	long long int maximum = 0;
	int n, i, j; scanf("%d", &n);
	
	scanf("%d", &tri_table[0][0]);

	for (i = 1; i < n; i++) {
		for (j = 0; j <= i; j++) {
			scanf("%d", &tri_table[i][j]);
			if (j == 0) {
				tri_table[i][j] += tri_table[i - 1][0];
				if (maximum < tri_table[i][j]) maximum = tri_table[i][j];
			}
			else if (j == i) {
				tri_table[i][j] += tri_table[i - 1][j - 1];
				if (maximum < tri_table[i][j]) maximum = tri_table[i][j];
			}
			else {
				tri_table[i][j] += max(tri_table[i - 1][j - 1], tri_table[i - 1][j]); 
				if (maximum < tri_table[i][j]) maximum = tri_table[i][j];
			}
		}
	}
	printf("%lld\n", maximum);
	return 0;
}

long long int power(int n) {
	return (n * (n + 1)) / 2;
}