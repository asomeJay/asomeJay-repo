/* 히스토그램에서 가장 큰 직사각형 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#define MAX_HV 100001
#define CHK 1
#define UNCHK 0
#define ll long long int

using namespace std;

vector<int> seg_tree;
vector<int> histogram;
int n_of_rectangle;

void init(int node, int start, int end);
int query(int node, int start, int end, int left, int right);
ll largest(int start, int end);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	int i, j, k;
	
	while (true) {
		cin >> n_of_rectangle;
		if (n_of_rectangle == 0) break;

		histogram.resize(n_of_rectangle + 1, 0);
		seg_tree.resize(pow(2, ceil(log2(n_of_rectangle) + 1)) , 0);

		for (i = 0; i < n_of_rectangle; i++) {
			cin >> histogram[i];
		}

		init(1, 0, n_of_rectangle - 1);
		cout << largest(0, n_of_rectangle - 1) << '\n';
	}

	return 0;
}

void init(int node, int start, int end) {
	int left_child, right_child;
	left_child = node * 2;
	right_child = node * 2 + 1;
	if (start == end)
		seg_tree[node] = start;

	else {

		init(left_child, start, (start + end) / 2);
		init(right_child, (start + end) / 2 + 1, end);
		// 오른쪽 자식이 더 크다. 
		if (histogram[seg_tree[left_child]] < histogram[seg_tree[right_child]]) {
			seg_tree[node] = seg_tree[left_child];
		} else {
			seg_tree[node] = seg_tree[right_child];
		}
	}
}

int query(int node, int start, int end, int left, int right) {
	if (end < left || right < start)
		return -1;
	if (start >= left && end <= right) {
		return seg_tree[node];
	}
	int left_child, right_child;
	left_child = 2 * node; right_child = 2 * node + 1;

	int qleft = query(left_child, start, (start + end) / 2, left, right);
	int qright = query(right_child, (start + end) / 2 + 1, end, left, right);
	if (qleft == -1)
		return qright;
	if (qright == -1)
		return qleft;
	else {
		if (histogram[qleft] < histogram[qright]) {
			return qleft;
		} else {
			return qright;
		}
	}
}

ll largest(int start, int end) {
	int mini = query(1, 0, n_of_rectangle - 1, start, end);
	ll area = (ll)(end - start + 1) * (ll)histogram[mini];

	if (start <= mini - 1) {
		ll temp = largest(start, mini - 1);
		if (area < temp)
			area = temp;
	}

	if (end >= mini + 1) {
		ll temp = largest(mini + 1, end);
		if (area < temp)
			area = temp;
	}
	return area;
}


