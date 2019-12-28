/* 가장 긴 바이토닉 부분 수열 */

#include <iostream>

using namespace std;

int seq[1001];
int r_seq[1001];
int l_seq[1001];

int p_point;

int main(void) {
	int n, t, i, i_c, j, k, ans, r_max, l_max;
	scanf("%d", &n);

	for (i = 1; i <= n; i++) {
		scanf("%d", &seq[i]);
		r_seq[i] = 1;
		l_seq[i] = 1;
	}

	ans = 1;

	for (i = 1, i_c = n; i <= n, i_c > 0; i++, i_c--) {
		r_max = 0;
		for (j = 1; j < i; j++) {
			if (seq[i] > seq[j]) {
				if (r_max < r_seq[j]) {
					r_max = r_seq[j];
				}
			}
		}
		r_seq[i] = r_max + 1;
	}

	for(i_c = n-1; i_c > 0 ; i_c--){
		l_max = 0;
		for (k = n; k > i_c; k--) {
			if (seq[i_c] > seq[k]) {
				if (l_max < l_seq[k]) {
					l_max = l_seq[k];
				}
			}
		}
		l_seq[i_c] = l_max + 1;
		
//		printf("i : %d  seq : %d   l_seq : %d   r_seq : %d   l+r : %d\n",
//			i_c, seq[i_c], l_seq[i_c], r_seq[i_c], 
//			l_seq[i_c] + r_seq[i_c]);
		if (ans < r_seq[i_c] + l_seq[i_c]) {
			ans = r_seq[i_c] + l_seq[i_c] - 1;
			p_point = i_c;
		}
	}

	
	
	printf("%d\n", ans);


	return 0;
}