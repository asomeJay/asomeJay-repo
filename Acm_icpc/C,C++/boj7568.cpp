/* µ¢Ä¡ */

#include <iostream>
#define MAX 51
using namespace std;

class student {
public:
	int weight, height, cnt;
	student(int a, int b) {
		this->weight = a;
		this->height = b;
		this->cnt = 0;
	}
	student() { ; }

	void in(int a, int b, int c) {
		this->weight = a;
		this->height = b;
		this->cnt = 1;
	}
	void rankup() {
		this->cnt++;
	}

};

student people[MAX];

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int a, b;
		cin >> a >> b;
		people[i].in(a, b, N);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			if (people[i].height < people[j].height &&
				people[i].weight < people[j].weight) {
				people[i].rankup();
			}
		}
	}

	for (int i = 0; i < N; i++)
		cout << people[i].cnt << " ";


	return 0;
}