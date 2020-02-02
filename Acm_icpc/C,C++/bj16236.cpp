/* 아기상어 */

#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <algorithm>

#define EAT 1
#define CAN 1
#define NO_EAT 0
#define MAX_SEA 22
#define OUT_OF_RANGE 0
#define IN_RANGE 1
#define MAX_DIST 2100000000

using namespace std;

/* 다 먹었는지 체크 */
bool is_eat();
bool comp(const tuple<int, int, int> &a, const tuple<int, int, int> &b) {
	
	if (get<0>(a) < get<0>(b)) {
		return true;
	}
	else if (get<0>(a) == get<0>(b)) {
		if (get<1>(a) < get<1>(b))
			return true;
		else if (get<1>(a) == get<1>(b))
			return get<2>(a) < get<2>(b);
	}

	return false;
}
/* 타켓을 찾는 함수 */
pair<int, int> find_target(int, int);

/* 그냥 상어 함수(여기서 다함) */
void main_of_shark(int, int);

bool is_range(int, int);

// 아기 상어 크기, 시간
int s_of_shark, t_of_eat, N, eat_fish;
int sea[MAX_SEA][MAX_SEA], f_target[MAX_SEA][MAX_SEA];
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int i, j, s_r, s_c;
	cin >> N;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			cin >> sea[i][j];

			if (sea[i][j] == 9) {
				sea[i][j] = 0;
				s_r = i; s_c = j;
			}
		}
	}

	s_of_shark = 2;

	main_of_shark(s_r, s_c);

	cout << t_of_eat << '\n';

	return 0;
}

/* Input :NONE
output : 만약 먹을 고기가 있으면 EAT, 없으면 NO_EAT을 반환 */
bool is_eat() {
	int i, j, flag = 0;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			if (sea[i][j] == 0 || sea[i][j] >= s_of_shark)
				continue;
			flag = 1;
			break;
		}
	}
	return flag;
}

pair<int, int> find_target(int sr, int sc) {
	int dist, r ,c, t;
	pair<int, int> target;
	vector<tuple<int, int, int>> value_cord;

	fill(&f_target[0][0], &f_target[MAX_SEA-1][MAX_SEA], 0);

	queue<pair<int, int>> q;
	queue<int> time;

	q.push(make_pair(sr, sc));
	time.push(0);

	while (!q.empty()) {
		r = q.front().first;
		c = q.front().second;
		t = time.front();
		q.pop(); time.pop();

		if (sea[r][c] != 0 && sea[r][c] < s_of_shark) {
			value_cord.emplace_back(t,r,c);
		}
	
		for (int i = 0; i < 4; i++) {
			int n_r = r + dr[i];
			int n_c = c + dc[i];

			if (is_range(n_r, n_c) == IN_RANGE && sea[n_r][n_c] <= s_of_shark && f_target[n_r][n_c] == 0) {
					q.push(make_pair(n_r, n_c));
					time.push(t + 1);
					f_target[n_r][n_c] = t + 1;
			}
		}
	}

	if (value_cord.size() == 0) {
		return make_pair(0, 0);
	}
	sort(value_cord.begin(), value_cord.end(), comp);

	t_of_eat += get<0>(value_cord[0]);

	target.first = get<1>(value_cord[0]);
	target.second = get<2>(value_cord[0]);
	return target;
}

void main_of_shark(int r, int c) {
	pair<int, int> target;
	int n_r, n_c;
	n_r = r; n_c = c;
	while (is_eat() == CAN) {
		target = find_target(n_r, n_c);

		if (target.second == 0) {
			return;
		}
		n_r = target.first;
		n_c = target.second;

		sea[n_r][n_c] = 0;
		eat_fish++;

		if (eat_fish == s_of_shark) {
			s_of_shark++;
			eat_fish = 0;
		}
	}
}

bool is_range(int r, int c) {
	return r >= 1 && r <= N && c >= 1 && c <= N;
}