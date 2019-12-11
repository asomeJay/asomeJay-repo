/* DP : 나무 자르기 */

#include <iostream>
#include <algorithm>

//#define SWAP(a, b) {int t; t = a; a = b; b = t;}

using namespace std;

long long int dp[1000001];
long long int binary_search(long long int left, long long int right, long long int);

int main(void) {
	long long int M, high = 0, result;
	long long int n, i; cin >> n >> M; // n = 나무 개수 M = 나무 길이
	for (i = 0; i < n; i++)
		scanf("%d", &dp[i]);

	sort(dp, dp + n);
	
	cout << binary_search(0, n, M) << endl;

	return 0;
}

long long int binary_search(long long int left_, long long int right_, long long int target) {
	long long int temp, height, i, left, right, result= 0;
	//left = left_; right = right_ - 1;
	height = (0 + dp[right_-1]) / 2;
	left = 0; right = dp[right_-1];
	while ( left <= right ) {
		/*if (before_height == height) 
			break;*/
	//	before_height = height;
		temp = 0;

		for (i = 0; i < right_; i++) {
			if (dp[i] <= height) continue;
			temp += dp[i] - height;
		}

		if (temp == target) return height;

		else if (temp > target) {
			left = height + 1;			
			if (result <= height) result = height;
		}

		else if (temp < target) {
			right = height - 1;
		}
		height = (left + right) / 2;
		
	}
	return result;
}