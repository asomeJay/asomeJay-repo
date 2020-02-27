/* 미생물 격리 */

/* Input
이중 배열을 전역변수로 선언하고 거기에 Input data를 받는다.
*/

/*Implementation 
void move() 는 모든 미생물을 정해진 방향으로 움직이게 한다. 
i) 움직이려는 곳이 약품이 칠해진 곳이면 미생물 수를 절반으로 줄인다.(0이면 그냥 없앤다.)
ii) 절반으로 줄이고 이동방향을 반대로 바꾼다. 만약 이동하려는 곳에 미생물이 있더라도 
이 과정은 진행한다. 
만약 움직이려는 곳에 이미 미생물이 있다면
i) 그 미생물의 Time_Stamp를 검사해서 이 미생물과 동일하면 -> 이 미생물을 그 미생물의 뒤에 넣는다(push_back)
ii) 그 미생물의 Time_Stamp가 더 작으면 이미 이동한 미생물이므로 둘을 합친다. (void combine())
ii-2) 합칠 때 이동방향은 미생물 수가 더 많은 애의 방향으로 한다. 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define MAX_AREA 102
#define EMPTY 0

using namespace std;

class microbe {
public:
	int index, r, c, n_of_cluster, direction;
	microbe(int a, int b, int cc, int d) {
		this->r = a;
		this->c = b;
		this->n_of_cluster = cc;
		this->direction = d;

	}
	microbe() { ; }
};

struct cmp {
	bool operator()(microbe a, microbe b) {
		if (a.r != b.r) {
			return a.r > b.r;
		}
		else {
			return a.c > b.c;
		}
	}
};

priority_queue < microbe, vector<microbe>, cmp> m_q;

int CELL, TIME, CLUSTER;
int dr[5] = { 0, -1,1,0,0 };
int dc[5] = { 0, 0,0,-1,1 };

void move(); // 모든 미생물을 움직이게 하는 함수
int direction_change(int dir); // 방향을 정반대로 바꿔주는 함수
bool is_touch(int r, int c); // 미생물이 빨간 염료가 칠해진 공간에 있는지 검사하는 함수 
int sum();

int main(void) {
	int i, j, t_case;
	int row, col, cluster, direct;
	cin >> t_case;

	microbe t;

	for (i = 1; i <= t_case; i++) {		
		cin >> CELL >> TIME >> CLUSTER;

		for (j = 0; j < CLUSTER; j++) {
			cin >> row >> col >> cluster >> direct;

			t = microbe(row, col, cluster, direct);
			m_q.push(t);
		}

		for (j = 1; j <= TIME; j++) 
			move();
		
		cout << "#" << i << " " << sum() << '\n';
	}

	return 0;
}
/*
void move() 는 모든 미생물을 정해진 방향으로 움직이게 한다.
i) 움직이려는 곳이 약품이 칠해진 곳이면 미생물 수를 절반으로 줄인다.(0이면 그냥 없앤다.)
ii) 절반으로 줄인 후 이동방향을 반대로 바꾼다*/

void move() {
	microbe t_m, f, s;
	priority_queue<microbe, vector<microbe>, cmp> t;

	while(!m_q.empty()){
		t_m = m_q.top();
		m_q.pop();

		t_m.r += dr[t_m.direction];
		t_m.c += dc[t_m.direction];

		/*염료가 칠해진 곳이면 군체수를 절반으로 줄이고 방향을 정반대로 바꾼다. */
		if (is_touch(t_m.r, t_m.c)) {
			
			t_m.n_of_cluster /= 2;
			t_m.direction = direction_change(t_m.direction);

		/* 군체 수가 0이면 더 이상 생각할 필요도 없으니 queue에 넣지도 않을거임*/
			if (t_m.n_of_cluster == EMPTY)
				continue;
		}

		t.push(t_m);
	}

	if (t.empty())
		return;

	f = t.top(); t.pop();
	
	int max_d, max_v, s_v;

	while (!t.empty()) {

		max_d = f.direction;
		max_v = f.n_of_cluster;
		s_v = f.n_of_cluster;

		s = t.top(); t.pop();
		while (f.r == s.r && f.c == s.c) {
			if (max_v < s.n_of_cluster) {
				max_d = s.direction;
				max_v = s.n_of_cluster;
			}

			s_v += s.n_of_cluster;
			if (t.empty()) {
				m_q.push(microbe(f.r, f.c, s_v, max_d));
				return;
			}

			f = s;
			s = t.top(); t.pop();
		}

		m_q.push(microbe(f.r, f.c, s_v, max_d));

		f = s;
	}
	m_q.push(f);
}

int direction_change(int dir) {
	switch (dir) {
	case 1:
		return 2;
	case 2:
		return 1;
	case 3:
		return 4;
	case 4:
		return 3;
	default :
		cout << "Direction_Change(int dir) Error " << '\n';
	}
}

bool is_touch(int r, int c) {
	return (r <= 0 || r >= CELL - 1) || (c <= 0 || c >= CELL - 1);
}

int sum() {
	int j;
	j = 0;
	while (!m_q.empty()) {
		microbe t_m = m_q.top();

		m_q.pop();
		j += t_m.n_of_cluster;
	}

	return j;
}