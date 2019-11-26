#include <iostream>

using namespace std;

int main(void) {

	int card_count, target_number, i, j, k ,flag, sum, mini_distance, the_value;
	int* card_arr;
	scanf("%d", &card_count); scanf("%d", &target_number);
	card_arr = (int*)malloc(sizeof(int) * card_count);
	for (i = 0; i < card_count; i++) {
		scanf("%d", &card_arr[i]);
	}
	mini_distance = 9999999999;
	for (i = 0; i < card_count - 2; i++) {
		for (j = i + 1; j < card_count - 1; j++) {
			for (k = j + 1; k < card_count; k++) {
				sum = card_arr[i] + card_arr[j] + card_arr[k];

				if ((mini_distance > (int)abs(sum - target_number)) && (sum <= target_number)) {
					mini_distance = (int)abs(sum - target_number);
					the_value = sum;
				}
			}
		}
	}
	cout << the_value << endl;
	return 0;
}
