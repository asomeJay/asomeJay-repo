k	/* 프렉탈 평면 */

#include <iostream>
#include <cmath>

#define WHITE 0
#define BLACK 1

using namespace std;

int Time, N, K, R1, R2, C1, C2, Biggest;

int getColor(int r, int c);
bool is_middle(int r, int c, int);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> Time >> N >> K >> R1 >> R2 >> C1 >> C2;
	
	Biggest = pow(N, Time);
	for (int i = R1; i <= R2; i++) {
		for (int j = C1; j <= C2; j++) {
			cout << getColor(i, j);
		}
		cout << '\n';
	}

	return 0;
}

int getColor(int r, int c) {
	int t_big = Biggest;
	int tr = r, tc = c, pr, pc;
	while ((t_big /= N)!= 0) {
		// 어떤 칸인지 알아보자!
		pr = tr / t_big;
		pc = tc / t_big;

		if (is_middle(pr, pc, t_big / N) == true) {
			return BLACK;
		}
		tr -= (pr * t_big);
		tc -= (pc * t_big);
	}
	return WHITE;
}

bool is_middle(int r, int c, int k) {
	int sp = (N - K) / 2;
	int fp = sp + K;
	if((sp <= r && r < fp) && (sp <= c && c < fp))
		return true;
	return false;
}