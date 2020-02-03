/* 내려가기 */

#include <iostream>
#include <algorithm>

using namespace std;
pair<int, int> a[3];
int N;

int main(void) {
	int temp, f_a, f_b, s_a, s_b, t_a, t_b;
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N; 
	cin >> a[0].first >> a[1].first >> a[2].first;
	for (int i = 0; i < 3; i++) {
		a[i].second = a[i].first;
	}
	
	for (int i = 0; i < N - 1; i++) {
		cin >> temp;
		f_a = min(a[0].first, a[1].first) + temp;
		f_b = max(a[0].second, a[1].second) + temp;

		cin >> temp;
		s_a = min(a[2].first, min(a[0].first, a[1].first)) + temp;
		s_b = max(a[2].second , max(a[0].second, a[1].second)) + temp;

		cin >> temp;
		t_a = min(a[1].first, a[2].first) + temp;
		t_b = max(a[1].second, a[2].second) + temp;

		a[0].first = f_a; a[0].second = f_b;
		a[1].first = s_a; a[1].second = s_b;
		a[2].first = t_a; a[2].second = t_b;
	}

	cout << max(a[0].second, max(a[1].second, a[2].second)) << " " << min(a[0].first, min(a[1].first, a[2].first))
		 << '\n';

	return 0;
}