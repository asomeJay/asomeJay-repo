/* ¿µÈ­°¨µ¶ ¼ó */

#include <iostream>
#include <string>

using namespace std;
// 666 - 1
// 1666 ~ 5666, 6660 ~ 6669, 7666 ~ 9666 - 18
// 10666 ~ 19666 - 19, 20666 ~ 29666 -19
// 66600 ~ 66699 - 100, 70666 ~ 99666 - 57
// 100666 ~ 199666 - 
// 1
// 1 x 8 + 10 
// 19 x 8 + 100
// a(n) = 8 * a(n-1) + 10^(n-1) 

int main(void) {
	cin.tie(NULL);
	int N;
	cin >> N;
	int cnt = 1, i = 666;
	while (cnt < N) {
		i++;
		if (to_string(i).find("666") != string::npos)
			cnt++;
	}

	cout << i;
	return 0;
}