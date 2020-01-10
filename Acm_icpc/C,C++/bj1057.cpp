/* bj1057 토너먼트 */

#include <iostream>

using namespace std;

int main(void) {
	int n_of_people, kim, lim, large, small, count;
	scanf("%d %d %d", &n_of_people, &kim, &lim);
	if (kim > lim) {
		large = kim;
		small = lim;
	}

	else {
		large = lim;
		small = kim;
	}
	count = 0;
	while (large != small) {
		large++;
		large /= 2;
		small++;
		small /= 2;
		count++;
	}

	printf("%d\n", count);
	return 0;
}