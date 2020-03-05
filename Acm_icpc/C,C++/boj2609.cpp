/* 최대공약수와 최소공배수 */

#include <iostream>

using namespace std;

int multi();
int N, M;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	int result = multi();
	cout << result << '\n' << N * M * result;
	return 0;
}

int multi() {
	int comp = 2;
	int result = 1;
	while (comp <= N && comp <= M) {
		if (N % comp == 0 && M % comp == 0) {
			N /= comp; M /= comp;
			result *= comp;
			comp = 2;
			continue;
		}
		comp++;
	}

	return result;

}