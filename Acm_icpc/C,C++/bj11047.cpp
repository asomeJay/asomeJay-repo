/* Greedy Algorithm : µ¿Àü 0 */

#include <iostream>
#include <array>

using namespace std;

// Coin infinite
int coin_count = 0;

int main(void) {
	int sort_of_coin, sum_of_coin, i, temp_sum = 0;
	cin >> sort_of_coin >> sum_of_coin;
	array<int, 10> coin;

	for (i = 0; i < sort_of_coin; i++) {
		cin >> coin[i];
	//	cout << "first for" << endl;
	}

	for (i = 0; i < sort_of_coin && coin[i] < sum_of_coin; i++);
	i--;

	while (1) {
	//	cout << "second while " << endl;

		while (temp_sum <= sum_of_coin) {
			coin_count++;
			temp_sum += coin[i];
		}
		temp_sum -= coin[i]; coin_count--;
		if (temp_sum == sum_of_coin) break;
		i--;
	}


	cout << coin_count << endl;


	return 0;
}