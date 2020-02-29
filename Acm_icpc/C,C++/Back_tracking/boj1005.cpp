/* ACM Craft */

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_BUILD 1001
#define VISIT 1
#define UNVISIT 0

using namespace std;

int acm_craft(int ind);
void init();

int Ans, Destination;
vector<pair<int, int>> build[MAX_BUILD];
vector<int> build_time;
int dist[MAX_BUILD];
int is_visit[MAX_BUILD];

int main(void) {
	int t_case, n_city, n_rule, win_city;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> t_case;

	for (int i = 0; i < t_case; i++) {
		init();
		cin >> n_city >> n_rule;
		for (int j = 1, t; j <= n_city; j++) {
			cin >> t;
			build_time.push_back(t);
		}
		
		for (int j = 0, t_a, t_b; j < n_rule; j++) {
			cin >> t_a >> t_b;
			//build[t_a].push_back({ t_b, build_time[t_b] });
			build[t_b].push_back({ t_a, build_time[t_a] });
		}

		cin >> Destination;

		cout << acm_craft(Destination) << '\n';
	}

	return 0;
}

int acm_craft(int ind) {
	/*
	if (ind == Destination) {
		return build_time[ind];
	}*/

	if (is_visit[ind] == VISIT) {
		return dist[ind];
	}

	is_visit[ind] = VISIT;

	if (build[ind].empty()) {
		dist[ind] = build_time[ind];
	}

	int t = -1;
	for (int i = 0; i < build[ind].size(); i++) {
		t = acm_craft(build[ind][i].first);
		t += build_time[ind];
	//	cout << "ind " << ind  << " : " << " " << t << endl;
		dist[ind] = max(dist[ind], t);
	}
	return dist[ind];
}

void init() {
	for (int j = 0; j < MAX_BUILD; j++) {
		build[j].clear();
		dist[j] = -1;
		is_visit[j] = false;
	}
	build_time.clear();
	build_time.push_back(0);

}