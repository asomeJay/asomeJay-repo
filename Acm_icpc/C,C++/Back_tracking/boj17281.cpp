/* 具备 */

#include <iostream>
#include <vector>
#include <algorithm>

#define OUT 0
#define HITS 1
#define DOUBLE 2
#define TRIPLE 3
#define HOMERUN 4
#define INNING_OUT 3

using namespace std;

int hitter[51][10];
int my_permutation[9] = { 2,3,4,5,6,7,8,9,1 };
int total_inning, out, hitter_num;
int base[4];

int hits(int);
int inning_play(int inning);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int i, j, k, grade, t_sum, score;
	vector<int> a;
	cin >> total_inning;
	for (i = 1; i <= total_inning; i++) {
		for (j = 1; j <= 9; j++) {
			cin >> hitter[i][j];
		}
	}
	score = 0;

	while (next_permutation(my_permutation, my_permutation + 8)) {
		
		k = my_permutation[3];
		my_permutation[3] = my_permutation[8];
		my_permutation[8] = k;

		t_sum = 0; hitter_num = 0;
		for (i = 1; i <= total_inning; i++) 
			t_sum += inning_play(i);
			
		score = max(score, t_sum);

		k = my_permutation[3];
		my_permutation[3] = my_permutation[8];
		my_permutation[8] = k;
	}

	cout << score << '\n';
	return 0;
}

int hits(int baseball_hits) {
	int i, t_score;
	t_score = 0;
	if (baseball_hits == OUT) {
		out++;
		return 0;
	}

	switch (baseball_hits) {
	case HITS: // 救鸥
		if (base[3] == 1)
			t_score++;
		base[3] = base[2];
		base[2] = base[1];
		base[1] = 1;
		break;
	case DOUBLE: // 2风鸥
		if (base[3] == 1)
			t_score++;
		if (base[2] == 1)
			t_score++;
		base[3] = base[1];
		base[2] = 1;
		base[1] = 0;
		break;
	case TRIPLE: // 3风鸥
		for (i = 1; i <= 3; i++) {
			if (base[i] == 1)
				t_score++;

			base[i] = 0;
		}
		base[3] = 1;
		break;
	case HOMERUN: // 权繁
		for (i = 1; i <= 3; i++) {
			if (base[i] == 1)
				t_score++;
			base[i] = 0;
		}
		t_score++;
		break;
	default:
		cout << "WTF" << endl;
	}
	
	return t_score;
}

int inning_play(int inning) {
	int j, t_score;
	t_score = 0;

	while (1) {
		t_score += hits(hitter[inning][my_permutation[hitter_num]]);
		if (out == INNING_OUT) {
			for (j = 1; j <= 3; j++)
				base[j] = 0;
			out = 0;
			hitter_num = (hitter_num + 1) % 9;
			return t_score;
		}

		hitter_num = (hitter_num + 1) % 9;
	}
}
