/* 트리의 지름 */

#include <iostream>
#include <list>
#include <vector>

#define MAX_TREE 10001

using namespace std;

vector<pair<int, int>> tree[MAX_TREE];
int longest(int, int);
int max(int, int);
int ans;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n_of_node, tree_index;
	cin >> n_of_node;
	int parent, child, weight;
	tree_index = 1;

	for (int i = 1; i < n_of_node; i++) {
		cin >> parent >> child >> weight;
		tree[parent].push_back({ child, weight });
	}

	longest(1, 0);
	cout << ans << '\n';
	return 0;
}

int longest(int parent, int sum) {
	int i, j, result, result2;
	result = 0; result2 = 0;
	
	for (i = 0; i < tree[parent].size(); i++) {
		int t_result = longest(tree[parent][i].first, tree[parent][i].second);
		if (result < t_result) {
			result2 = result;
			result = t_result;
		}
		else if (result2 < t_result) {
			result2 = t_result;
		}
		
	}
	ans = max(ans,result + result2);
	return sum + result;
}

int max(int a, int b) {
	if (a < b) return b;
	else
		return a;
}