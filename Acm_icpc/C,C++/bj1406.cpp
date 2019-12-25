/* ฟกต๐ลอ */

#include <iostream>
#include <stack>

using namespace std;

stack<char> l, r;
int seq_size;

void L();
void D();
void B();
void P();

int main(void) {
	int i, j, k, n;
	char order,c;

	c = getchar();

	while (c != EOF && c != '\n' && c != '\0') {
		l.push(c);
		c = getchar();
	}

//	printf("cursor : %d     size : %d\n", cursor, seq_size);
	//cin >> seq;
	//cursor = seq.size();

	scanf("%d", &n);

	for (i = 0; i < n; i++) {
	scanf(" ");

		scanf("%c", &order);
		switch (order) {
		case 'L' :
			L();
			break;
		case 'D' :
			D();
			break;
		case 'B':
			B();
			break;
		case 'P' :
			P();
			break;
		}
	}

	while (!l.empty()) {
		r.push(l.top());
		l.pop();
	}
	
	while (!r.empty()) {
		printf("%c", r.top());
		r.pop();
	}

	return 0;
}

void L() {
	if (!l.empty()) {
		r.push(l.top());
		l.pop();
	}
}

void D() {
	if (!r.empty()) {
		l.push(r.top());
		r.pop();
	}
}

void B() {
	int i;
	if (!l.empty()) {
		l.pop();
	}

}

void P() {
	char c;
	scanf(" ");
	scanf("%c", &c);

	int i;
	l.push(c);
}