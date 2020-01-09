/* ·Îº¿ Ã»¼Ò±â */

#include <iostream>

using namespace std;

int N, M, clean;
int space[52][52];
bool visit[52][52];
pair<int, int> left_turn[4];
pair<int, int> m_forward[4];
pair<int, int> m_backward[4];

void cleaning(int, int, int);

int main(void) {
	int i, j, r_r, r_c, r_d;

	scanf("%d %d", &N, &M);
	scanf("%d %d %d", &r_r, &r_c, &r_d);
	r_r++; r_c++;
	left_turn[0] = make_pair(0, -1);
	left_turn[1] = make_pair(-1, 0);
	left_turn[2] = make_pair(0, 1);
	left_turn[3] = make_pair(1, 0);

	m_forward[0] = make_pair(-1, 0);
	m_forward[1] = make_pair(0, 1);
	m_forward[2] = make_pair(1, 0);
	m_forward[3] = make_pair(0, -1);

	m_backward[0] = make_pair(1, 0);
	m_backward[1] = make_pair(0, -1);
	m_backward[2] = make_pair(-1, 0);
	m_backward[3] = make_pair(0, 1);
	
	for (i = 1; i <= N + 1; i++) {
		visit[i][0] = visit[i][M + 1] = 1;
		space[i][0] = space[i][M + 1] = 1;
	}
		
	for (i = 1; i <= M + 1; i++) {
		visit[0][i] = visit[N + 1][i] = 1;
		space[0][i] = space[N + 1][i] = 1;
	}
	
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++) {
			scanf("%d", &space[i][j]);
			if (space[i][j] == 1) {
				visit[i][j] = 1;
			}
		}
			
	}

	cleaning(r_r, r_c, r_d);
	printf("%d\n", clean);

	return 0;
}

void cleaning(int r_, int c_, int d_) {
	if (visit[r_][c_] != 1) {
		visit[r_][c_] = 1;
		clean++;
	}

	int n_r, n_c, n_d, r, c, d, count;

	r = r_; c = c_; d = d_; count = 0;
	// a 
	while (1) {
		n_r = r + left_turn[d].first; n_c = c + left_turn[d].second;

		switch (d) {
		case 0:
			n_d = 3; break;
		case 1:
			n_d = 0; break;
		case 2:
			n_d = 1; break;
		case 3:
			n_d = 2; break;
		default:
			printf("error\n");
		}

		if (space[n_r][n_c] != 1 && visit[n_r][n_c] != 1) {
			d = n_d;
			//r = n_r + m_forward[d].first; c = m_forward[d].second;
			r = n_r; c = n_c;
			visit[r][c] = 1; clean++;
			count = 0;
		}

		// b
		else {
			if (count < 4) {
				d = n_d;
				count++;
			}
			else {
				count = 0;
				if (space[r + m_backward[d].first][c + m_backward[d].second] != 1) {
					r += m_backward[d].first;
					c += m_backward[d].second;
				}
				else {
					return;
				}
			}
		}
	}
}