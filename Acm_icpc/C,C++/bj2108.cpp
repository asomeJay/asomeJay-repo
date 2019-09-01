#include <iostream>
#include <stdlib.h>
#include <cmath>

#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))

void middleNum(int[], int, int); // Áß¾Ó°ª
void frequentNum(int[], int, int); // ÃÖºó°ª


void mergeSort(int list[], int left,int right);
void merge(int list[], int left, int mid, int right);
//int partition(int[], int, int);
//void quickSort(int[], int, int);

using namespace std;
int* sorted;

int main() {
	int testcase{}, * list, sum{ 0 };
	cin >> testcase;
	list = (int*)malloc(sizeof(int) * testcase);
	sorted = (int*)malloc(sizeof(int) * testcase);
	for (int i = 0; i < testcase; i++) {
		cin >> list[i];
		sum += list[i];
	}

	mergeSort(list, 0, testcase-1);
	
	cout << round(sum / (double)testcase) << endl;
	middleNum(list, 0, testcase - 1);
	frequentNum(list, 0, testcase - 1);
	cout << list[testcase - 1] - list[0] << endl;
}

void middleNum(int list[], int left, int right) {
	
	cout << list[right / 2] << endl;
}

void frequentNum(int list[], int left, int right) {
	int i, j, min = 0, minValue = 0, overWriting = 0;
	int count, pivot;

	for (i = left; i <= right; i++) {
		pivot = list[i];
		count = 0;
		
		while (pivot == list[i]) {
			count++;
			i++;
		}
		--i;
		if (min < count) {
			min = count;
			minValue = list[i];
			overWriting = 0;
		}
		else if (min == count && !overWriting) {
			overWriting++;
			minValue = list[i];
		}
	}

	cout << minValue << endl;
}


void mergeSort(int list[], int left, int right) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;
		mergeSort(list, left, mid);
		mergeSort(list, mid + 1, right);
		merge(list, left, mid, right);
	}

}

void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}

	if (i > mid) {
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];
		}
	}
	else {
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];
		}
	}

	for (l = left; l <= right; l++)
		list[l] = sorted[l];
		
}
/*
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
		} while (high >= low && list[high] >= pivot);

		if (low < high)
			SWAP(list[low], list[high], temp);

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
*/