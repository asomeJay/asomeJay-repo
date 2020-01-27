/* 감시 */

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_OFFICE 10
#define WALL 6

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define OUT_OF_RANGE 0
#define IN_RANGE 1

using namespace std;

int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };
int N, M, mini;
int office[MAX_OFFICE][MAX_OFFICE];
vector < pair<int, int>> cctv_cord; 
vector<int> cctv_kind;

/* 주어진 매개변수가 정상적인 범위인지 체크해서
  정상범위이면 IN_RANGE를 return 하고 아니라면 OUT_OF_RANGE를 출력 */
bool is_range(int, int);

/* 매개변수로 cctv의 종류와 row값과 col 값, CCTV가 바라보는 방향과
CCTV가 설치된 field를 받는다.
*/

void cctv_monitor(int, int, int, int dir, int field[][MAX_OFFICE]);

/*  CCTV의 사각지대를 찾는, 이 프로그램의 대표 함수 */
void cctv_blind_spot(int, int[][MAX_OFFICE]);

/* 매개변수로 CCTV의 행과 열의 값을 주고 그 CCTV가 바라보는 방향을 준다.
그리고 그 CCTV가 설치된 배열도 매개변수로 줌으로써 
CCTV의 종류에 따라, CCTV가 바라보는 방향에 위치한 0을 #으로 바꿔준다. */
void dir_conquer(int r, int c, int dir, int field[][MAX_OFFICE]);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int i, j;
	cin >> N >> M;

	/* cctv_cord와 cctv_kind는 전역변수로 선언되었다.
	cctv_cord에는 각 cctv의 좌표값이 pair<int,int> 자료형으로 저장되어있고
	cctv_kind에는 그 좌표에 존재하는 cctv의 종류가 저장되어 있다. */

	cctv_cord.push_back(make_pair(NULL, NULL));
	cctv_kind.push_back(NULL);

	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++) {
			cin >> office[i][j];
			if(office[i][j] == 0)
				mini++;

			if (office[i][j] >= 1 && office[i][j] <= 5) {
				cctv_cord.push_back(make_pair(i, j));
				cctv_kind.push_back(office[i][j]);
			}
		}
	}

	//cctv_kind.size()가 1이라는 건 cctv가 존재하지 않는다는 의미이므로
	// 칸 개수 전체(mini의 초기값)를 출력한다. 
	if (cctv_kind.size() != 1) 
		cctv_blind_spot(1, office);
	
	cout << mini << '\n';
	return 0;
}

bool is_range(int r_, int c_) {
	if (r_ >= 1 && r_ <= N && c_ >= 1 && c_ <= M) {
		return IN_RANGE;
	}
	return OUT_OF_RANGE;
}

/* dir로 들어올 수 있는 값은 NORTH, EAST, SOUTH, WEST 밖에 없다. */
void dir_conquer(int r_, int c_, int dir, int field[][MAX_OFFICE]) {
	int r, c;
	r = r_; c = c_;

	/*행과 열의 값이 정상범위를 벗어나거나 
	  벽을 만날때까지 계속 #으로 만든다. */

	while (is_range(r, c) == IN_RANGE && office[r][c] != WALL) {
		field[r][c] = '#';
		r += dr[dir];
		c += dc[dir];
	}
}

void cctv_blind_spot(int index, int field[][MAX_OFFICE]) {
	int i, j, cctv_k, countt = 0;

	/* index값이 cctv_kind.size()라는 건 vecor의 끝에 다다랐다는 의미이므로
	남아있는 0의 개수를 세고 현재까지의 최솟값과 비교해서 최소값 
	mini를 갱신한다. */
	if (index >= cctv_kind.size()) {
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= M; j++) {
				if (field[i][j] == 0)
					countt++;
			}
		}

		mini = min(mini, countt);
		return;
	}
	
	int t_field[MAX_OFFICE][MAX_OFFICE];

	cctv_k = cctv_kind[index];

	/* 
	cctv_k = cctv_kind 
	  cctv 종류가 5가 아니라면 네 번 돌린다(방향 바꿔가면서)
	  물론 cctv 2번같은 경우 돌릴 수 있는 방법이 두 종류만 존재하지만
	  가독성을 위해서 퉁쳤다. 
	*/
	if (cctv_k != 5) {
		for (i = 0; i < 4; i++) {
			copy(&field[0][0], &field[MAX_OFFICE - 1][MAX_OFFICE - 1],
				&t_field[0][0]);

			cctv_monitor(cctv_k, cctv_cord[index].first, cctv_cord[index].second,
				i, t_field);
			cctv_blind_spot(index + 1, t_field);
		}
	}

	else {
		copy(&field[0][0], &field[MAX_OFFICE - 1][MAX_OFFICE - 1],
			&t_field[0][0]);

		cctv_monitor(5, cctv_cord[index].first, cctv_cord[index].second,
			i, t_field);
		cctv_blind_spot(index + 1, t_field);
	}
}

/* cctv의 종류를 숫자로 받아서 그에 걸맞게 처리한다. */
void cctv_monitor(int cctv_kind, int r, int c, int dir, int field[][MAX_OFFICE]) {
	switch (cctv_kind) {
	case 1:
		dir_conquer(r, c, dir, field);
		break;
	case 2:
		dir_conquer(r, c, dir, field);
		dir_conquer(r, c, (dir + 2) % 4, field);
		break;
	case 3:
		dir_conquer(r, c, dir, field);
		dir_conquer(r, c, (dir + 1) % 4, field);
		break;
	case 4:
		dir_conquer(r, c, dir, field);
		dir_conquer(r, c, (dir + 1) % 4, field);
		dir_conquer(r, c, (dir + 2) % 4, field);
		break; 
	case 5:
		dir_conquer(r, c, NORTH, field);
		dir_conquer(r, c, EAST, field);
		dir_conquer(r, c, SOUTH, field);
		dir_conquer(r, c, WEST, field);
		break;
	default : 
		cout << "WFT";
	}
}