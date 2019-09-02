#include <iostream>

#define SWAP(x,y,temp) ((temp) = (y), (y) = (x), (x) = (temp))
using namespace std;

int partition(int list[], int left, int right);
void quickSort(int list[], int left, int right);

int main() {
	int i, intNum, *howManyNum;
	cin >> intNum;

	howManyNum = (int*)malloc(sizeof(int) * intNum);
	for (i = 0; i < intNum; i++) 
		cin >> howManyNum[i];

	quickSort(howManyNum, 0, intNum - 1);

	cout << howManyNum[0] << " " << howManyNum[intNum - 1];
	return 0;
}

int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];

	do {
		do {
			low++;
		} while (low <= high && list[low] <= pivot);
		do {
			high--;
		} while (low <= high && list[high] >= pivot);

		if (low < high) {
			SWAP(list[low], list[high], temp);
		}
	} while (low < high);

	SWAP(list[left], list[high], temp);

	return high;
}

void quickSort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);

		quickSort(list, left, q - 1);
		quickSort(list, q + 1, right);
	}
}