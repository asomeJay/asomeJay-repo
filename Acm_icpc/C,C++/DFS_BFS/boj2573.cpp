/* ºù»ê */

#include <iostream>
#include <list>
#include <stack>

#define MAX_MAP 301
#define WATER 0
using namespace std;

class iceberg_ {
public:
	int r, c, value;
	iceberg_(int rr, int cc, int vv) {
		this->r = rr;
		this->c = cc;
		this->value = vv;
	}
};

bool dfs();
bool meltdown();

int ROW, COL, n_of_iceberg, year;
int map[MAX_MAP][MAX_MAP];
list<iceberg_>iceberg;

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int i, j, k;
	cin >> ROW >> COL;

	for (i = 1; i <= ROW; i++) {
		for (j = 1; j <= COL; j++) {
			cin >> map[i][j];
			if (map[i][j] != 0) {
				iceberg.push_back(iceberg_(i, j, map[i][j]));
				n_of_iceberg++;
			}
		}
	}
	while (meltdown());

	if (iceberg.empty()) 
		cout << "0\n";
	else
		cout << year << '\n';

	return 0;
}

bool meltdown() {
	if (iceberg.empty()) return false;
	
	int nr, nc;
	year++;

	for (auto i = iceberg.begin(); i != iceberg.end(); i++) {
		for (int j = 0; j < 4; j++) {
			nr = i->r + dr[j];
			nc = i->c + dc[j];

			if (map[nr][nc] == WATER) {
				i->value--;
			}
		}
	}

	for (auto i = iceberg.begin(); i != iceberg.end(); ) {
		if (i->value <= WATER) {
			i->value = WATER;
		}

		map[i->r][i->c] = i->value;

		if (i->value == WATER) {
			n_of_iceberg--;
			auto k = i;
			i++;
			iceberg.erase(k);
		}
		else 
			i++;
		
	}

	return dfs();
}

bool dfs() {
	int i, j, r, c, nr, nc, cc;
	cc = 0;

	bool is_visit[MAX_MAP][MAX_MAP] = { 0, };
	stack<pair<int, int>> s;

	s.push(make_pair(iceberg.begin()->r, iceberg.begin()->c));
	is_visit[iceberg.begin()->r][iceberg.begin()->c] = true;
	cc++;

	while (!s.empty()) {
		r = s.top().first; c = s.top().second;
		s.pop();

		for (i = 0; i < 4; i++) {
			nr = r + dr[i];
			nc = c + dc[i];
			if (is_visit[nr][nc] == 0 && map[nr][nc] != WATER) {
				cc++;
				is_visit[nr][nc] = true;
				s.push(make_pair(nr, nc));
			}
		}
	}
	if (cc != n_of_iceberg) 
		return false;
	
	return true;
}
