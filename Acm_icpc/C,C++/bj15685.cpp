/* 드래곤 커브 */

#include <iostream>
#include <vector>

#define E 0
#define N 1
#define W 2
#define S 3
#define MAX_TABLE 150

using namespace std;

pair<int, int> rotated(pair<int, int> a, pair<int,int>, int dir);
void dragon_curve(vector<pair<int, int>> a, int);

int dy[4] = { -1, 0, 1, 0};
int dx[4] = { 0, 1, 0, -1};
int table[MAX_TABLE][MAX_TABLE];
vector<int> dir;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	vector<pair<int, int>> a;

	int t_case, x, y, d, g, i, generation;
	cin >> t_case;

	for (i = 1; i <= t_case; i++) {
		a.clear(); dir.clear();
		dir.push_back(0);
		cin >> x >> y >> d >> g;
		a.push_back(make_pair(y, x));
		dir.push_back(d);

		switch (d) {
		case 0:
			a.push_back(make_pair(y, x+1));
			break;
		case 1:
			a.push_back(make_pair(y-1, x));
			break;
		case 2:
			a.push_back(make_pair(y, x-1));
			break; 
		case 3:
			a.push_back(make_pair(y+1, x));
			break;
		}

		dragon_curve(a, g);
		/*
		for (int k = 0; k <= 10; k++) {
			for (int j = 0; j <= 10; j++) {
				cout << table[k][j];
			}
			cout << '\n';
		}
		cout << '\n' << '\n';*/

	}
	
	int counts = 0;
	for (i = 0; i < MAX_TABLE-1; i++) {
		for (int j = 0; j < MAX_TABLE-1; j++) {
			if (table[i][j] != 0 &&
				table[i + 1][j] != 0 &&
				table[i][j + 1] != 0 &&
				table[i + 1][j + 1] != 0)
				counts++;
		}
	}

	cout << counts;
	return 0;
}

// a가 온 방향이 dir이다. 
pair<int, int> rotated(pair<int, int> a, pair<int,int> junction, int direct) {
	pair<int, int> new_a;
	new_a = a;
	 // first == y, second == x;
	switch (direct) {
	case E:
		new_a.first = junction.first + dy[0];
		new_a.second = junction.second + dx[0];
		dir.push_back(N);
		break;
	case N:
		new_a.first = junction.first + dy[3];
		new_a.second = junction.second + dx[3];
		dir.push_back(W);
		break;
	case W:
		new_a.first = junction.first + dy[2];
		new_a.second = junction.second + dx[2];
		dir.push_back(S);
		break;
	case S:
		new_a.first = junction.first + dy[1];
		new_a.second = junction.second + dx[1];
		dir.push_back(E);
		break;
	default : 
		cout << "hihi" << '\n';
	}

	return new_a;
}

void dragon_curve(vector<pair<int, int>> a,int generation) {
	int i, j, t_size;
	vector<pair<int, int>>temp;
	
	pair<int, int> end_point, tmp;

	temp = a;
	end_point = temp[temp.size() - 1];

	for (i = 1; i <= generation; i++) {
		t_size = temp.size();

		for (j = t_size - 1; j >= 1; j--) {
			end_point = rotated(temp[j], end_point, dir[j]);
			temp.push_back(end_point);
		}
	}

	for (i = 0; i < temp.size(); i++) {
		table[temp[i].first][temp[i].second]++;
	}
}
