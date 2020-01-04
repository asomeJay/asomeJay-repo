/* 하노이 탑 */

#include <iostream>

using namespace std;

void one_two(int depth);
void one_three(int depth);
void two_one(int depth);
void two_three(int depth);
void three_one(int depth);
void three_two(int depth);

int hanoi[21];

int main(void) {
	int circular;
	cin >> circular;

	int i, j, k;
	hanoi[1] = 1;
	for (i = 2; i <= circular; i++) {
		hanoi[i] = 2 * hanoi[i - 1] + 1;
	}
	printf("%d\n", hanoi[circular]);

	if (circular == 1) {
		printf("1 3\n");
		return 0;
	}

	one_three(circular);
	return 0;
}

void one_two(int depth) {
	if (depth == 2) {
		printf("1 3\n");
		printf("1 2\n");
		printf("3 2\n");
	}
		
	else {
		one_three(depth - 1);
		printf("1 2\n");
		three_two(depth - 1);
	}
}

void one_three(int depth) {
	if (depth == 2) {
		printf("1 2\n");
		printf("1 3\n");
		printf("2 3\n");
	}

	else {
		one_two(depth-1);
		printf("1 3\n");
		two_three(depth-1);
	}
}

void two_one(int depth) {
	if (depth == 2) {
		printf("2 3\n");
		printf("2 1\n");
		printf("3 1\n");
	}
	else {
		two_three(depth - 1);
		printf("2 1\n");
		three_one(depth - 1);
	}
}

void two_three(int depth) {
	if (depth == 2) {
		printf("2 1\n");
		printf("2 3\n");
		printf("1 3\n");
	}
	else {
		two_one(depth - 1);
		printf("2 3\n");
		one_three(depth - 1);
	}
}

void three_one(int depth) {
	if (depth == 2) {
		printf("3 2\n");
		printf("3 1\n");
		printf("2 1\n");
	}
	else {
		three_two(depth - 1);
		printf("3 1\n");
		two_one(depth - 1);
	}
}

void three_two(int depth) {
	if (depth == 2) {
		printf("3 1\n");
		printf("3 2\n");
		printf("1 2\n");
	}
	else {
		three_one(depth - 1);
		printf("3 2\n");
		one_two(depth - 1);
	}
}