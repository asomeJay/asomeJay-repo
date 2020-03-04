/* ¼ö Ã£±â */

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 100000 + 1

using namespace std;

int N, M, A;
vector<int> a;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N; a.resize(N); 
	
	for (int i = 0; i < N; i++) 
		cin >> a[i];
	
	sort(a.begin(), a.end());

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> A;
		if (binary_search(a.begin(), a.end(), A))
			cout << 1 << '\n';
		else
			cout << 0 << '\n';
	}

	return 0;
}