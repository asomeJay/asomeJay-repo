#include <iostream>
#include <stdlib.h>

using namespace std;

void insert(int[], int, int *);
int del(int[], int*);
int main(void) {
	int i, temp, chi, dif = 1;
	int top, *list__;
	(top) = 0;
	list__ = (int*)malloc(sizeof(int) * 10);

	for (i = 0; i < 10; i++) {
		cin >> temp;
		insert(list__, temp % 42, &top);
	}
	chi = del(list__, &top);
	int lis;
	for (i = 1; i < 10; i++) {
		lis = del(list__, &top);
		if (lis != chi) {
			dif++;
			chi = lis;
		}
	}

	cout << dif << endl;

	free(list__);
	return 0;
}

void insert(int list[], int data, int*top) {
	int n = (*top)++;
//	cout << "data : " << data << endl;
	while ((n != 0) && list[n / 2] > data) {
		list[n] = list[n / 2];
		n /= 2;
	}
	list[n] = data;
//	cout << "list N : " << list[n] << endl;
}

int del(int list[], int*top) {
	int end = list[--(*top)];
	int ret = list[0];
	int child, parent;
	parent = 0;
	child = 1;
	while (child <= *(top)) {
		if ((child < *(top)) && list[child] > list[child + 1]) child++;
		if (list[child] > end) break;

		list[parent] = list[child];
		parent = child;
		child *= 2;
	}
	list[parent] = end;
	return ret;
}