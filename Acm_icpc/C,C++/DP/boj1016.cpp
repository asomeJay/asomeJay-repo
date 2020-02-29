/* Á¦°ö ¤¤¤¤ ¼ö*/

#include <iostream>
#include <algorithm>
#include <tgmath.h>

#define ll long long int
#define MIN_MAX 1000001

using namespace std;

bool min_to_max[MIN_MAX];
ll Mini, Maxi, Ans, Subs, t, down, s_num, Sqrt;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  cout.tie(NULL);
	cin >> Mini >> Maxi;

	Subs = Maxi - Mini + 1;

	down = 2; Sqrt = (ll)sqrt(Maxi);
	while ((t = (ll)pow(down++, 2)) <= Maxi) {
		s_num = Mini % t;
		if (t < Mini && s_num != 0) {
			s_num = ((Mini / t) + 1) * t - Mini;
		}
		if (t >= Mini) {
			s_num = t - Mini;
		}
		/*
		if (min_to_max[s_num] == true)
			continue;
			*/
		while (s_num < Subs) {
		//	cout << "??" << endl;
			min_to_max[s_num] = true;
			s_num += t;
		}
	}
	
	for (int i = 0; i < Subs; i++) {
		//cout << min_to_max[i] << " ";
		if (min_to_max[i] == false)
			Ans++;
	}

	cout << Ans;

	return 0;
}