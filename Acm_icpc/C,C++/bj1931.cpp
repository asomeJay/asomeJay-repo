/* Greedy : 회의실 배정 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> meeting_time;
/*
class meeting {
public:
	int s_time;
	int f_time;

	meeting(int s, int f);
	meeting();

	bool meeting_comp(meeting const * a, meeting const * b);
};

meeting::meeting(int s, int f) {
	this->s_time = s;
	this->f_time = f;
}

meeting::meeting() { ; }

bool meeting_comp(vector<pair<int, int>> const a, vector<pair<int, int>> const b) {
	return  < b->s_time;
}*/

bool sort_by_finish(const pair<int, int>& a, const pair<int, int>& b) {
	if (a.second != b.second) {
		return a.second < b.second;
	}
	else if (a.second == b.second) {
		return a.first < b.first;
	}
}

int is_used;

int main(void) {
	int meeting_count, i, j, s, f, ans, depth ; scanf("%d", &meeting_count);

	for (i = 0; i < meeting_count; i++) {
		scanf("%d %d", &s, &f);
		meeting_time.push_back(make_pair(s,f));
	}
	
	sort(meeting_time.begin(), meeting_time.end(), sort_by_finish);

	depth = 0;

	for (i = 0; i < meeting_count; i++) {
		if (is_used <= meeting_time[i].first) {
			is_used = meeting_time[i].second;
			depth++;
		}
	}

	printf("%d\n", depth);


	return 0;
}