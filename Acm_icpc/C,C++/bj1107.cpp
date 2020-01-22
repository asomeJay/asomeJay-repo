/* 리모콘 */

/* 결국 주어진 수와 가장 가까운 수를 만드는 문제 */

#include <iostream>
#include <string>
#include <algorithm>

#define UPPERBOUND 1000000
#define LOWERBOUND 0
#define REMOTE 11
#define BREAK 1
#define NORMAL 0
#define INT_MAX 10000000
#define UNMATCHED -1

using namespace std;

int N, n_of_button, mini, size_channel;
bool remote[REMOTE];
string ans, channel;

int nearest_num(int target);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int i, j, broken_button, int_channel;

	cin >> channel; 
	int_channel = stoi(channel);
	size_channel = channel.size();

	cin >> broken_button;
	for (i = 1; i <= broken_button; i++) {
		cin >> j;
		remote[j] = BREAK;
	}
	mini = abs(100 - int_channel);
	int tt = nearest_num(int_channel);
	int temp = abs(int_channel - tt) + to_string(tt).size();
	if (tt != UNMATCHED && mini > temp)
		mini = temp;

	cout << mini << endl;
	return 0;
}

int nearest_num(int target){
	int i, j, k;
	i = j = target;
	while (1) {
		if (i < LOWERBOUND && j > UPPERBOUND) return UNMATCHED;

		if (i >= LOWERBOUND) {
			string i_str = to_string(i);

			for (k = 0; k < i_str.size(); k++) {
				if (remote[i_str[k] - '0'] == BREAK) {
					break;
				}
			}
			if (k == i_str.size()) return i;
			i--;
		}
		
		if (j <= UPPERBOUND) {
			string j_str = to_string(j);
			for (k = 0; k < j_str.size(); k++) {
				if (remote[j_str[k]-'0'] == BREAK) break;
			}

			if (k == j_str.size()) return j;
			j++;
		}
	}
}