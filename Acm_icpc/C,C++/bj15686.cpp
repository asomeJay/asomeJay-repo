/* 치킨 배달 */
#include <iostream>
#include <vector>

using namespace std;

int N, M, smallest;
int street[52][52];
pair<int, int> chicken_market[14];

vector<pair<int, int>> chicken_axis;

void chick_select(int depth, int index);

int main(void) {
	int i, j;
	smallest = 1000000;
	scanf("%d %d", &N, &M);

	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			scanf(" %d", &street[i][j]);
			if (street[i][j] == 2) {
				chicken_axis.push_back(make_pair(i, j));
			}
		}
	}

	for (i = 0; i < chicken_axis.size(); i++) {
		chicken_market[1] = chicken_axis[i];
		chick_select(2, i);
	}

	printf("%d\n", smallest);
	return 0;
}

void chick_select(int depth, int index){
	int i, j, k, sum;

	/* 치킨집 다 골랐수다~ */
	if (depth > M) {
		int distance_from_chick[52][52];
		fill(&distance_from_chick[0][0], &distance_from_chick[51][52], 0);

		for (k = 1; k <= M; k++) {
			for (i = 1; i <= N; i++) {
				for (j = 1; j <= N; j++) {
					if (street[i][j] == 1) {
						int temp = abs(chicken_market[k].first - i) + abs(chicken_market[k].second - j);
						if (distance_from_chick[i][j] == 0) {
							distance_from_chick[i][j] = temp;
						}
						else {
							distance_from_chick[i][j] = (distance_from_chick[i][j] < temp ?
								distance_from_chick[i][j] : temp);
						}
					}
				}
			}
		}

		sum = 0;
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++) 
				sum += distance_from_chick[i][j];			
		}
		if (sum < smallest) smallest = sum;
		return;
	}

	for (i = index+1; i < chicken_axis.size(); i++) {
		chicken_market[depth] = chicken_axis[i];
		chick_select(depth + 1, i);
		chicken_market[depth] = make_pair(0, 0);
	}

}