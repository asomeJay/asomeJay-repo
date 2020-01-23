/* 캐슬 디펜스 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#define MAX_LAND 16
#define MAX_D 11
#define END 0
#define KEEP_GO 1
#define NOT_MATCHED -1

using namespace std;

int land[MAX_LAND][MAX_LAND];
int N, M, D;

vector<int>enemy[MAX_LAND];

/* 궁수의 위치를 받아서 공격하는 함수 */
void attack(int arc1, int arc2, int arc3);
void destroy(pair<int, int>);

/* 하나의 궁수 위치를 매개변수로 받아서 누구를 공격할 지 
결정하는 함수 */
pair<int,int> target_determine(int arc);

/* 거리 계산하는 함수 */
int dist(int r, int c, int n_r, int n_c);
void copy_vector(vector<int>[], vector<int>[]);

/* 공격이 끝나면 해야할 일을 하는 함수.*/
void after_attack();

bool is_end();

int counti, maxi;

int main(void) {
	/* for문 세개를 돌리면서 모든 궁수의 위치를 정한다. */
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int i, j, k;

	cin >> N >> M >> D;
	
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++) {
			cin >> land[i][j];
			// 적이 있는 땅이라면 마땅히 저장해줘야지. 
			if (land[i][j] == 1) {
				enemy[j].push_back(i);
			}
		}
	}
	vector<int> temporary_storage[MAX_LAND];
	copy_vector(temporary_storage, enemy);

	// 궁수의 위치를 조금씩 바꿔가면서 모든 경우의 수를 고려한다. 
	for (i = 1; i <= M; i++) {
		for (j = i + 1; j <= M; j++) {
			for (k = j + 1; k <= M; k++) {
				counti = 0;

				attack(i, j, k);

				maxi  = max(counti, maxi);
				copy_vector(enemy, temporary_storage);

			}
		}
	}

	cout << maxi << "\n";
	return 0;
}

void attack(int arc1, int arc2, int arc3) {
	// 1. 각 궁수의 공격 대상을 찾는다. choose()
	pair<int, int> target1, target2, target3;

	while (is_end() == KEEP_GO) {
		target1 = target_determine(arc1);
		target2 = target_determine(arc2);
		target3 = target_determine(arc3);

		// 2. 공격한다. (제거한다)
		destroy(target1); destroy(target2); destroy(target3);

		for (int i = 1; i <= M; i++) {
			if (!enemy[i].empty() && enemy[i].back() == 0) {
				enemy[i].pop_back();
			}
		}

		// 3. 적을 한 칸씩 내린다. after_attack()
		after_attack();
	}
}

/* 궁수가 공격할 대상 찾는 함수들 */
pair<int,int> target_determine(int arc) {
	int col, row, t_dist, ind_r, ind_c, mini;

	ind_r = ind_c = NOT_MATCHED;
	mini = INT_MAX;

	// 1) 거리가 D 이하여야 하고 
	for (col = 1; col <= M; col++) {
		if (enemy[col].empty()) continue;

		row = enemy[col].back();
		t_dist = dist(row, col, N + 1, arc);

		if (t_dist > D) continue;

	// 2) 가장 가까운 적이고
		if (mini > t_dist) {
			mini = t_dist;
			ind_c = col;
			ind_r = row;
		}
	}
	// 3) 그런 적이 많으면 가장 왼쪽을 공격한다.
	return make_pair(ind_r, ind_c);
}

/* 공격 후에 할 일들 */
void after_attack() {
	int i, j;
	for (i = 1; i <= M; i++) {
		if (enemy[i].empty()) continue;

		for (j = 0; j < enemy[i].size(); j++) {
			enemy[i][j]++;
		}

		if (enemy[i].back() > N) {
			enemy[i].pop_back();
		}
	}
}

void destroy(pair<int, int> target) {
	if (target.first == NOT_MATCHED \
		&& target.second == NOT_MATCHED)
		return;

	int r, c;
	r = target.first; c = target.second;

	if (enemy[c].back() != 0) {
		enemy[c].pop_back();
		enemy[c].push_back(0);
		counti++;
	}
}

int dist(int r, int c, int n_r, int n_c) {
	return abs(n_r - r) + abs(n_c - c);
}

bool is_end() {
	int i;
	for (i = 1; i <= M; i++) {
		if (enemy[i].empty())continue;
		return KEEP_GO;
	}
	return END;
}

void copy_vector(vector<int> temporary_storage[], vector<int> go[]) {
	int i, j;
	for (i = 1; i <= M; i++) {
		if (go[i].empty()) continue;
		for (j = 0; j < go[i].size(); j++) {
			temporary_storage[i].push_back(go[i][j]);
		}
	}
}