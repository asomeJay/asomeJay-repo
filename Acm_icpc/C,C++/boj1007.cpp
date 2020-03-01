/* º¤ÅÍ ¸ÅÄª */

#include <iostream>
#include <vector>
#include <stack>
#include <tgmath.h>
#include <algorithm>
#include <cstring>

#define N_DOT 21
#define ll long double

using namespace std;

pair<int, int>dot[N_DOT];
ll Ans = 9876543210, n_of_vector;

void init();
void combination();

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cout << fixed; cout.precision(12);

	int i, j, t_case;
	cin >> t_case;
	for (i = 1; i <= t_case; i++) {
		init();

		cin >> n_of_vector;
		for (j = 0; j < n_of_vector; j++) {
			int a, b;
			cin >> a >> b;
			dot[j] = { a,b };
		}

		combination();
		cout << Ans << '\n';
	}

	return 0;
}

void init() {
	Ans = 9876543210;
}

void combination() {
	vector<int> ind;
	int sel_vector = n_of_vector / 2;

	for (int i = 0; i < sel_vector ; i++) 
		ind.push_back(1);
	for (int i = 0; i < sel_vector; i++)
		ind.push_back(0);

	sort(ind.begin(), ind.end());
	do {
		ll sel_x = 0, sel_y = 0;
		ll unsel_x = 0, unsel_y = 0;

		for (int i = 0; i < n_of_vector; i++) {
			if (ind[i] == 1) {
				sel_x += dot[i].first;
				sel_y += dot[i].second;
			}
			else {
				unsel_x += dot[i].first;
				unsel_y += dot[i].second;
			}
		}
		ll x = (unsel_x - sel_x) * (unsel_x - sel_x);
		ll y = (unsel_y - sel_y) * (unsel_y - sel_y);
		Ans = min(Ans, sqrt((x + y)));
	} while (next_permutation(ind.begin(), ind.end()));


}