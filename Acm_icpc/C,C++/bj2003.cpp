/* 수들의 합 2 */

#include <iostream>

using namespace std;

int N, M, n_of_case;
int num[10005];

int main(void) {
	int i, j, k, s_p, f_p, t_sum;
	
	n_of_case = 0;

	scanf("%d %d", &N, &M);

	for (i = 1; i <= N; i++) 
		scanf("%d", &num[i]);
	
	s_p = 1; f_p = 1; t_sum = num[f_p];
	while (1) {
	//	printf("s_p : %d     f_p : %d  t_sum :   %d  \n", s_p, f_p, t_sum);

		if (f_p > N) break;
		if (f_p < s_p) {
			f_p = s_p;
			t_sum = num[f_p];
			continue;
		}
		if (t_sum > M) {

			t_sum -= num[s_p];
			s_p++;
		}
		else if (t_sum == M) {
			n_of_case++;
			t_sum -= num[s_p];
//			f_p++;
//			t_sum += num[f_p];
			s_p++;
		}

		else if (t_sum < M) {
			f_p++;
			t_sum += num[f_p];
		}
	}


	printf("%d\n", n_of_case);
	return 0;
}
