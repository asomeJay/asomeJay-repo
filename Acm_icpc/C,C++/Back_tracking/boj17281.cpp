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

int base[5], player[10];
vector<int> hitter[10];

int score, out,inning;

int hits(int);
void baseball_play(int, int, int);
int return_num(int n, int);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int i, j, k, grade;
	cin >> inning;
	for (i = 1; i <= 9; i++) {
		for (j = 1; j <= inning; j++) {
			cin >> grade;
			hitter[i].push_back(grade);
		}
	}

	baseball_play(1, 0, 0);

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
		break;
	case TRIPLE: // 3风鸥
		for (i = 1; i <= 3; i++) {
			if (base[i] == 1)
				t_score++;

			base[i] = 0;
		}
		break;
	case HOMERUN: // 权繁
		for (i = 1; i <= 4; i++) {
			if (base[i] == 1)
				t_score++;
			base[i] = 0;
		}
		t_score++;
		break;
	default : 
		cout << "WTF" << endl;
	}
	return t_score;

}

void baseball_play(int c_inning, int s_of_score, int n_of_player) {
	int i, j, c_score, c_ins, c_player;
	c_ins = c_inning;
	c_player = n_of_player;

	if (inning < c_ins) {
		score = max(s_of_score, score);
		return;
	}

	if (n_of_player % 9 == 0) {
		for (i = 1; i <= 9; i++) {
			player[i] = false;
		}
	//	n_of_player = 0;
	}

	for (i = 1; i <= 9; i++) {
		if (player[i] == true || (i == 1 && n_of_player % 9 != 3)) continue;

		player[i] = true;
		cout << i << " " << c_player << " " << out << " " << c_ins <<endl;
		c_score = s_of_score + hits(hitter[i][return_num(c_player, 9)]);
		if (out == INNING_OUT) {
			out = 0;
			if (c_ins + 1 > inning) {
				score = max(s_of_score, score);
				return;
			}
				
			baseball_play(c_ins + 1, c_score, c_player + 1);
		}
		
		else {
			baseball_play(c_ins, c_score, c_player + 1);
		}
		
		player[i] = false;
	}
}

int return_num(int n, int divisor) {
	if (n == 0)
		return 0;

	if (n % divisor == 0) {
		return n / divisor - 1;
	}
	else {
		return n / divisor;
	}
}