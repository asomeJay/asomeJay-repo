// 거리 최솟값 구하기

#include <iostream>
#include <algorithm>

using namespace std;

int x, y, w, h;

int main(void) {
	int maxi, t;

	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> x >> y >> w >> h;
	maxi = x;
	maxi = min(maxi, w - x);
	maxi = min(maxi, y);
	maxi = min(maxi, h - y);

	cout << maxi << '\n';
	return 0;
}