/* 에산 배정하기 */

#include <iostream>

using namespace std;

long long int r_budget[10001];

void up_lim();

long long int n_of_city, b_of_all, t_max, t_sum, ans;

int main(void) {
	
	int i;

	scanf("%lld", &n_of_city);

	t_max = 0; t_sum = 0;
	for (i = 1; i <= n_of_city; i++) {
		scanf("%lld", &r_budget[i]);

		t_sum += r_budget[i];
		if (t_max < r_budget[i]) {
			t_max = r_budget[i];
		}
	}

	scanf("%lld", &b_of_all);

	if (b_of_all > t_sum) {
		printf("%lld\n", t_sum);
		return 0;
	}

	up_lim();
	printf("%lld\n", ans);

	return 0;
}

void up_lim() {
	int i;
	long long int left, right, middle, mid_sum;

	left = 0; right = t_max; 

	while (left <= right) {
		mid_sum = 0;
		middle = (left + right) / 2;
		for (i = 1; i <= n_of_city; i++) {
			if (middle >= r_budget[i]) {
				mid_sum += r_budget[i];
			}
			else {
				mid_sum += middle;
			}
		}

		if (mid_sum > b_of_all) {
			right = middle - 1;
		}

		else if (mid_sum <= b_of_all) {
			if (ans < middle) {
				ans = middle;
			}
			left = middle + 1;

		}
	}
}