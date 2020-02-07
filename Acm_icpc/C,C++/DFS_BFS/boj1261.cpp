/* ¾Ë°í½ºÆÌ */

#include <iostream>
#include <algorithm>
#include <queue>

#define OUT_OF_RANGE 0
#define IN_RANGE 1
#define MAX_MAZE 101
#define IS_WALL 1
#define NOT_WALL 0
#define WALL 1

using namespace std;

class node {	
public:
	int wall, row, col;
	
	node(int w, int r, int c) {
		this->wall = w;
		this->row = r;
		this->col = c;
	}	
};

struct LessThanByAge
{
	bool operator()(const node& lhs, const node& rhs) const
	{
		if (lhs.wall != rhs.wall) {
			return lhs.wall > rhs.wall;
		}
		else {
			if (lhs.row != rhs.row) {
				return lhs.row > rhs.row;
			}
			else {
				return lhs.col > rhs.col;
			}
		}
	}
};
int Row, Col;
int maze[MAX_MAZE][MAX_MAZE];
int dp_maze[MAX_MAZE][MAX_MAZE];
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0 , -1 };
priority_queue<node, vector<node>, LessThanByAge> q;

bool is_range(int r, int c);

int main(void) {

	cin >> Col >> Row;
	for (int i = 1; i <= Row; i++) {
		getchar();
		for (int j = 1; j <= Col; j++) {
			maze[i][j] = getchar() - '0';
		}
	}

	int r, c, w;
	fill(&dp_maze[0][0], &dp_maze[MAX_MAZE - 1][MAX_MAZE], 1000000);

	q.push(node(0, 1, 1));
	dp_maze[0][0] = 0;

	while (!q.empty()) {
		
		w = q.top().wall;
		r = q.top().row;
		c = q.top().col;
		q.pop();

		if (r == Row && c == Col) {
			cout << w << '\n';
			return 0;
		}

		for (int i = 0; i < 4; i++) {
			
			if (is_range(r + dr[i], c + dc[i]) == IN_RANGE) {
				if (maze[r + dr[i]][c + dc[i]] == WALL && dp_maze[r+dr[i]][c+dc[i]] > w + 1) {
					dp_maze[r + dr[i]][c + dc[i]] = w + 1;
					q.push(node(w + 1, r + dr[i], c + dc[i]));
				}
				else if(maze[r+dr[i]][c+dc[i]] != WALL && dp_maze[r + dr[i]][c + dc[i]] > w) {
					dp_maze[r + dr[i]][c + dc[i]] = w;
					q.push(node(w, r + dr[i], c + dc[i]));
				}
			}
		}

	}
}

bool is_range(int r, int c) {
	return 1 <= r && r <= Row && 1 <= c && c <= Col;
}