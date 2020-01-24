/* 집합의 표현 */

//#include <iostream>
#include <cstdio>

#define NODE_MAX 1000001
#define OPERATION_MAX 100001
#define UNION 0
#define CONFORM 1
#define YES 1
#define NO 0

using namespace std;

void unions(int, int);
bool checks(int tar1, int);
int find_parent(int);

int parent[NODE_MAX];
int ranki[NODE_MAX];

int main(void) {
//	ios_base::sync_with_stdio(false);
//	cin.tie(0); cout.tie(0);

	int operation;
	int n, m, tar1, tar2, temp;

	scanf("%d %d", &n, &m);
	//cin >> n >> m;
	for (int i = 1; i <= n; i++) {
	//while(n--){
		parent[i] = i;
		ranki[i] = 1;
	}
		
	for (int i = 1; i <= m; i++) {
//	while(m--){
		//getchar();
		//cin >> temp >> tar1 >> tar2;
		scanf("%d %d %d", &temp, &tar1, &tar2);
		operation = temp;

		switch (operation) {
		case UNION :
			unions(tar1, tar2);
			break;

		case CONFORM : 
			if (checks(tar1, tar2) == YES)
				printf("YES\n");
				//cout << "YES\n";
			else
				printf("NO\n");
				//cout << "NO\n";
			break;
		}
	}

	return 0;
}

void unions(int tar1, int tar2) {
	int uni1 = find_parent(tar1);
	int uni2 = find_parent(tar2);

	if (uni1 == uni2) return;
	
	if (ranki[uni1] == ranki[uni2]) {
		parent[uni2] = uni1;
		ranki[uni1]++;
	}

	else if (ranki[uni1] > ranki[uni2]) 
		parent[uni2] = uni1;

	else 
		parent[uni1] = uni2;
}

bool checks(int tar1, int tar2) {
	return find_parent(tar1) == find_parent(tar2);
}

int find_parent(int target) {
	/*
	if (parent[target] == target) return target;
	else 
		return parent[target] = find_parent(parent[target]);*/
	
	int t_parent = parent[target];
	int temp = target;

	while (t_parent != parent[t_parent]) {
		t_parent = parent[t_parent];
	}

	while (t_parent != parent[temp]) {
		parent[temp] = t_parent;
	}

	return t_parent;
}